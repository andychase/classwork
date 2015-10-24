from redis.client import Redis

redis = Redis()


def delete(host):
    # Delete website if one exists
    # Return value is True if one existed, False if not
    if host:
        return redis.delete(host)
    else:
        return False
