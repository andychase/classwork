"""
List Server
Andy Chase

Usage:

python list_server.py serv
"""
import sys
import redis
import json
import uuid
import hashlib
from flask import Flask, jsonify, request
app = Flask(__name__)


r = redis.StrictRedis(host='localhost', port=6379, db=0, decode_responses=True)

def make_hash(input_message):
	m = hashlib.sha256()
	m.update(input_message.encode('utf-8'))
	return m.hexdigest()


def register(username, password):
	r"""
	>>> register("a", "b").keys()
	dict_keys(['id'])
	>>> bool(register("a", "b"))
	True
	>>> register("a", "b")
	{'id': ''}
	"""
	user_id = str(uuid.uuid4())
	
	response = r.get("user_" + username)
	if response:
		return {'id': ''}
	else:
		r.set("user_" + username, user_id)
		r.set("user_" + username + make_hash(password + user_id), user_id)
		return {'id': user_id}


def login(username, password):
	"""
	>>> bool(register("a", "b"))
	True
	>>> login("a", "b") != {'id': -1}
	True
	"""
	user_id = r.get("user_" + username)
	
	response = r.get("user_" + username + make_hash(password + user_id))
	if response == user_id:
		return {'id': user_id}
	else:
		return {'id': ''}

def get_list(get_user_list, user_id):
	"""
	>>> bool(register("a", "b"))
	True
	>>> id = login("a", "b")['id']
	>>> set_list(False, "", [])
	{'ok': True}
	>>> get_list(False, "")
	{'list': []}
	>>> set_list(False, "", ["1", "2"])
	{'ok': True}
	>>> get_list(False, "")
	{'list': ['1', '2']}
	>>> set_list(True, id, [])
	{'ok': True}
	>>> get_list(True, id)
	{'list': []}
	>>> set_list(True, id, ["3", "4"])
	{'ok': True}
	>>> get_list(True, id)
	{'list': ['3', '4']}
	"""
	if get_user_list:
		key = "userid_" + user_id
	else:
		key = "global_list"

	response = json.loads(r.get(key))
	return {'list': response}


def set_list(get_user_list, user_id, data):
	if get_user_list:
		key = "userid_" + user_id
	else:
		key = "global_list"

	r.set(key, json.dumps(data))
	return {'ok': True}


@app.route("/register", methods=["POST"])
def _register():
	username = request.form.get("username")
	password = request.form.get("password")
	return jsonify(register(username, password))


@app.route("/login", methods=["POST"])
def _login():
	username = request.form.get("username")
	password = request.form.get("password")
	return jsonify(login(username, password))


@app.route("/get")
def _get_list():
	get_user_list = request.args.get("get_user_list") == "true"
	user_id = request.args.get("user")
	return jsonify(get_list(get_user_list=get_user_list, user_id=user_id))


@app.route("/set", methods=["POST"])
def _set_list():
	data = request.get_json()
	get_user_list = data["get_user_list"] == "true"
	user_id = data["user"]
	data = data["data"]
	
	return jsonify(set_list(get_user_list, user_id, data))


if __name__ == "__main__":
	if len(sys.argv) == 2:
		app.run(debug=False)
	else:
		with app.test_request_context('/'):
			import doctest
			doctest.testmod()
