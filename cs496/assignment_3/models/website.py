from app import redis


def delete(host):
    if host:
        host_keys = redis.keys(host + "*")
        if host_keys:
            redis.delete(*host_keys)
        return True
    else:
        return False
