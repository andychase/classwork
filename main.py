import os

from views import app

if __name__ == "__main__" and os.getenv('DEBUG', 'true') == 'true':
    app.run(debug=True)
