import os
from flask import Flask
from views import app


class FlaskConfig(object):
    DEBUG = os.getenv('DEBUG', 'true') == 'true'
    REDIS_URL = os.getenv('REDIS_URL', '')


app.config.from_object(FlaskConfig)

redis_store = FlaskRedis(app)
if os.getenv('DEBUG', 'true') == 'true':
    app.run(debug=True)
