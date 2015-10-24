from flask import Flask, jsonify
from flask import request
from models import magnet, website

app = Flask(__name__)


@app.route('/site/delete', methods=["delete"])
def site_delete():
    result = website.delete(request.form.get("host"))
    return jsonify({'ok': result})


@app.route('/mag/make', methods=["post"])
def mag_make():
    return jsonify({'ok': True})


@app.route('/mag/remove', methods=["delete"])
def mag_add():
    return jsonify({'ok': True})


@app.route('/mag/delete', methods=["delete"])
def mag_delete():
    return jsonify({'ok': True})


@app.route('/mag/move', methods=["post"])
def mag_move():
    return jsonify({'ok': True})
