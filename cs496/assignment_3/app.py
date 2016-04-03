import os
from flask import Flask
from flask.ext.redis import FlaskRedis
from redis import StrictRedis

app = Flask(__name__)


class FlaskConfig(object):
    DEBUG = os.getenv('DEBUG', 'true') == 'true'
    REDIS_URL = os.getenv('REDIS_URL', '')


app.config.from_object(FlaskConfig)


class DecodedRedis(StrictRedis):
    @classmethod
    def from_url(cls, url, db=None, **kwargs):
        kwargs['decode_responses'] = True
        return StrictRedis.from_url(url, db, **kwargs)


redis = FlaskRedis.from_custom_provider(DecodedRedis, app)
redis.decode_responses = True
