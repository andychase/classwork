"""
Predict.py

Usage: python predict.py <image>
"""
import sys
from contextlib import contextmanager

import numpy as np
import time
from PIL import Image
from keras.models import model_from_json
from keras.optimizers import SGD

img_rows = 64
img_cols = 64
img_channels = 1
batch_size = 32
nb_epoch = 20


def load_image(filename):
    img = Image.open(filename)
    img.load()
    img = img.resize((128, 128), Image.BICUBIC)
    img.thumbnail((img_cols, img_rows))
    a4im = Image.new('RGB',
                     (img_cols, img_rows),
                     (255, 255, 255))

    a4im.paste(img, (0, 0))

    return np.array([np.array(a4im.convert("L"))])

if len(sys.argv) < 2:
    print(__doc__)
    exit(0)

image = np.array([load_image(sys.argv[1])])
nb_classes = 2

X_test = image.astype('float32')
X_test /= 255

sgd = SGD(lr=0.01, decay=1e-6, momentum=0.9, nesterov=True)
model = model_from_json(open('cnn_64_1.json').read())
model.load_weights('cnn_64_1.h5')
model.compile(loss='categorical_crossentropy',
              optimizer=sgd,
              metrics=['accuracy'])

@contextmanager
def measure_time():
    t1 = time.clock()
    yield
    t2 = time.clock()
    print('%s: %0.2f seconds elapsed' % ("", t2-t1))

with measure_time():
    if model.predict_classes(X_test, verbose=0)[0] == 0:
        print("")
        print("android")
    else:
        print("")
        print("iphone")

print(model.predict_proba(X_test, verbose=0))
