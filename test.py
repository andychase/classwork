import json
import uuid
import unittest

from main import app
from app import redis


class FlaskTestCase(unittest.TestCase):
    def setUp(self):
        app.config['TESTING'] = True
        self.app = app.test_client()
        self.site_host = str(uuid.uuid4())

    def tearDown(self):
        pass # self.delete_site()

    def make_site(self):
        self.app.post('/site/new', data=dict(
            site=self.site_host,
            style="",
            text="test",
            x=0,
            y=0
        ))

    def delete_site(self):
        self.app.delete('/site/delete/{}'.format(self.site_host))

    def get_site_data(self):
        response = self.app.get('/site/get/{}'.format(self.site_host))
        site_data = json.loads(response.data.decode())
        return site_data

    def test_create_and_destroy_site(self):
        def get_site_keys():
            return set(redis.keys(self.site_host + '*'))

        self.assertSetEqual(get_site_keys(), set())
        self.make_site()
        self.assertSetEqual(get_site_keys(), {
            self.site_host,
            self.site_host + "_1",
            self.site_host + "_magnet_index",
        })
        self.assertSetEqual(set(redis.sscan_iter(self.site_host)), {"1"})
        self.delete_site()
        self.assertSetEqual(get_site_keys(), set())

    def test_add_magnet(self):
        self.make_site()
        self.assertDictEqual(self.get_site_data(), {
            'mags': [
                dict(
                    style="",
                    text="test",
                    x=0,
                    y=0
                )
            ],
            'ok': True
        })

    def test_remove_magnet(self):
        self.make_site()
        self.app.delete('/mag/delete', data={
            'site': self.site_host,
            'mag_id': 1
        })
        self.assertDictEqual(self.get_site_data(), {
            'mags': [],
            'ok': True
        })

    def test_move_magnet(self):
        self.make_site()
        self.app.put(
            '/mag/move',
            data=dict(site=self.site_host, mag_id=1, x=10, y=10)
        )
        self.assertDictEqual(self.get_site_data(), {
            'mags': [
                {'style': '', 'text': 'test', 'x': 10, 'y': 10}
            ],
            'ok': True
        })


if __name__ == '__main__':
    unittest.main()
