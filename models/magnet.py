from redis.client import StrictRedis

redis = StrictRedis()


def _build_magnet_id(website_host, magnet_id):
    return "{}_{}".format(website_host, magnet_id)


def _get_single_magnet(website_host, magnet_id):
    return redis.hgetall(_build_magnet_id(website_host, magnet_id))


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


def get(website_host):
    yield redis.get(website_host + '_version')
    magnet_ids = redis.lrange(website_host, -1, -1)
    for magnet_id in magnet_ids:
        yield _get_single_magnet(website_host, magnet_id)


def move(website_host, magnet_id, x, y):
    new_version = redis.incr(website_host + '_version')
    redis.hmset(
        _build_magnet_id(website_host, magnet_id),
        dict(x=x, y=y)
    )
    # Add to website version log
    redis.zremrangebyscore(website_host + '_version_list', -1, new_version - 100)
    redis.zadd(website_host + '_version', " ".join((magnet_id, x, y)))


def poll(website_host, version):
    # Get changes since version from website changelog
    # If version too old, return false
    redis.zcount(website_host + '_version_list', version, version)
    versions = redis.zrangebyscore(website_host + '_version_list', version, -1)
    for version in versions:
        yield [int(i) for i in version.split(' ')]
