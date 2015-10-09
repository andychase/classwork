import json
import os

from flask import Flask, render_template, request
from flask.ext.redis import FlaskRedis
from flask import redirect, url_for

app = Flask(__name__)

IMAGE_DATA_KEY = 'image_data'


def save_image_data():
    image_data = {
        'image': request.form.get("images", "3vKIGia"),
        'upside_down': request.form.get("upside_down") is not None,
        'stretch': int(request.form.get("stretch", 0)),
        'color_change': request.form.get("color_change", ""),
        'words': request.form.get("words", "")[:1000]
    }
    if image_data['image'] not in {"3vKIGia", "b1cILHt"}:
        image_data['image'] = "3vKIGia"
    if image_data['color_change'] not in {"", "g", "b", "o"}:
        image_data['color_change'] = ""
    if image_data['stretch'] not in range(11):
        image_data['stretch'] = 0

    redis_store.set(IMAGE_DATA_KEY, json.dumps(list(image_data.items())))


def load_image_data(retry=False):
    image_data_string = redis_store.get(IMAGE_DATA_KEY)

    if image_data_string is None and retry is not True:
        save_image_data()
        return load_image_data(True)

    image_data = json.loads(image_data_string)
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
    DEBUG = os.getenv('DEBUG', 'true') == 'true'
    REDIS_URL = os.getenv('REDIS_URL', '')


app.config.from_object(FlaskConfig)

redis_store = FlaskRedis(app)
if os.getenv('DEBUG', 'true') == 'true':
    app.run(debug=True)
