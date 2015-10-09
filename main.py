import json
import os

from flask import Flask, render_template, request
from flask.ext.redis import FlaskRedis
from flask import redirect, url_for

app = Flask(__name__)

IMAGE_DATA_KEY = 'image_data'


def save_image_data():
    image_data = [
        ['image', request.form.get("images", "3vKIGia")],
        ['upside_down', request.form.get("upside_down") is not None],
        ['stretch', int(request.form.get("stretch", 0))],
        ['color_change', request.form.get("color_change", "")],
        ['words', request.form.get("words", "")]
    ]
    redis_store.set(IMAGE_DATA_KEY, json.dumps(image_data))


def load_image_data():
    image_data = json.loads(redis_store.get(IMAGE_DATA_KEY))
    if image_data is None:
        save_image_data()
        image_data = load_image_data()
    return image_data


@app.route('/')
def index():
    image_data = dict(load_image_data())
    return render_template('index.html', vars=image_data)


@app.route('/edit', methods=["get"])
def edit_get():
    image_variables = dict(load_image_data())
    return render_template('edit.html', vars=image_variables)


@app.route('/edit', methods=["post"])
def edit_post():
    save_image_data()
    return redirect(url_for('index'))


@app.route('/view')
def view():
    image_variables = load_image_data()
    return render_template('view.html', table=image_variables)


class FlaskConfig(object):
    DEBUG = os.getenv('DEBUG', True)
    REDIS_URL = os.getenv('REDIS_URL', '')


app.config.from_object(FlaskConfig)

redis_store = FlaskRedis(app)
if os.getenv('DEBUG', True):
    app.run(debug=True)
