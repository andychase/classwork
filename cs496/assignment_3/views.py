from flask import jsonify
from flask import request
from flask.ext.autodoc import Autodoc
from app import app

from models import magnet, website

auto = Autodoc(app)


@app.route('/site/delete/<site>', methods=["delete"])
@auto.doc()
def site_delete(site):
    """ Deletes all data associated with the requested site hostname.
    """
    return jsonify({'ok': website.delete(site)})


@app.route('/site/new', methods=["post"])
@app.route('/mag/make', methods=["post"])
@auto.doc()
def mag_make():
    """ Places a magnet on a site and returns the id
    Form Arguments:
    * site
    * text -- What the magnet says, max 60 chars
    * style -- Text css style, max 1000 chars
    * x -- X Position from the top of the screen
    * y -- Y Position from the left of the screen
    Note: This creates the site if none exists
    Note: /mag/make and /site/new are the same
    Example Reponse:
        {
          "id": "1",
          "ok": true
        }
    """
    return jsonify(dict(ok=True, id=magnet.new(
        website_host=str(request.form.get('site'))[:100],
        style=str(request.form.get('style'))[:1000],
        text=str(request.form.get('text'))[:60],
        x=int(request.form.get('x')),
        y=int(request.form.get('y')),
    )))


@app.route('/site/get/<site>', methods=["get"])
@auto.doc()
def site_get(site):
    """ Returns all the magnet information and positions for a site.
    If the requested site does not exist, the magnet list with be empty.
    Example response:
        {
          "mags": [
            {
              "style": "",
              "text": "test",
              "x": 10,
              "y": 10
            }
          ],
          "ok": true
        }
    """
    return jsonify({'ok': True, 'mags': list(magnet.get(site))})


@app.route('/mag/delete', methods=["delete"])
@auto.doc()
def mag_delete():
    """ Delete a single magnet from a site.
    Form arguments: site, mag_id
    """
    magnet.delete(
        request.form.get("site"),
        request.form.get("mag_id")
    )
    return jsonify({'ok': True})


@app.route('/mag/move', methods=["put"])
@auto.doc()
def mag_move():
    """ Move a single magnet.
    Form arguments: site, mag_id, x, y
    """
    magnet.move(
        request.form.get("site"),
        request.form.get("mag_id"),
        request.form.get("x"),
        request.form.get("y")
    )
    return jsonify({'ok': True})


@app.route('/')
def documentation():
    return auto.html()
