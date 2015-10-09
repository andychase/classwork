from flask import Flask, render_template

app = Flask(__name__)


@app.route('/')
def index():
    return render_template('index.html')


@app.route('/edit')
def edit():
    return render_template('edit.html')


@app.route('/view')
def view():
    return render_template('view.html')
