from app import redis


def _build_magnet_id(website_host, magnet_id):
    return "{}_{}".format(website_host, magnet_id)


def _get_single_magnet(website_host, magnet_id):
    redis.decode_responses = True
    details = redis.hgetall(_build_magnet_id(website_host, magnet_id))
    details['x'] = int(details['x'])
    details['y'] = int(details['y'])
    return details


def new(website_host, text, style, x, y):
    magnet_id = redis.incr(website_host + '_magnet_index')
    redis.hmset(
        _build_magnet_id(website_host, magnet_id),
        dict(text=text, style=style, x=x, y=y)
    )
    redis.sadd(website_host, magnet_id)
    return magnet_id


def delete(website_host, magnet_id):
    redis.srem(website_host, magnet_id)
    redis.delete(_build_magnet_id(website_host, magnet_id))


def get(website_host):
    magnet_ids = redis.sscan_iter(website_host, count=100)
    for magnet_id in magnet_ids:
        yield _get_single_magnet(website_host, int(magnet_id))


def move(website_host, magnet_id, x, y):
    redis.hmset(
        _build_magnet_id(website_host, magnet_id),
        dict(x=x, y=y)
    )
