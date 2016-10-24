import os
import statistics
import timeit
from contextlib import contextmanager

import numpy as np
import time
from PIL import Image
from skimage.filters import sobel
from sklearn import svm
from sklearn.cross_validation import cross_val_score
from sklearn.ensemble import RandomForestClassifier
from sklearn.neighbors import KNeighborsClassifier
from sklearn.ensemble import VotingClassifier


def load_image(filename):
    try:
        img = Image.open(filename)
    except OSError:
        return
    img.load()
    img.thumbnail((128, 128))
    a4im = Image.new('RGB',
                     (128, 128),
                     (255, 255, 255))

    a4im.paste(img, (0, 0))

    return np.array(a4im.convert("L"))


def load_all_images(directory, category):
    for root, dirs, files in os.walk(directory):
        for file in files:
            orig_image = load_image(os.path.join(root, file))
            if orig_image is None:
                continue
            image = np.array(orig_image).flatten()

            yield image, category


android_images = list(load_all_images('images/android', 0))
iphone_images_w = list(load_all_images('images/iphone_white', 1))
iphone_images_b = list(load_all_images('images/iphone_black', 1))
nb_classes = 2
print("img load")

train = android_images + iphone_images_w + iphone_images_b
data_train, labels_train = zip(*train)

t_models = {
    "knn, k=1": KNeighborsClassifier(n_neighbors=1),
    "RandomForest": RandomForestClassifier(),
    "LinearSVC": svm.LinearSVC(),
}

models = {
    "ens": VotingClassifier(tuple(t_models.items()))
}


@contextmanager
def measure_time():
    t1 = time.clock()
    yield
    t2 = time.clock()
    print('%s: %0.2f seconds elapsed' % ("", t2-t1))

print("{},{},{}".format("name", "mean", "std"))
for name, model in models.items():
    with measure_time():
        model.fit(data_train, labels_train)
    with measure_time():
        model.predict(data_train)
    # results = cross_val_score(model, data_train, labels_train, cv=30)
    #print("{},{},{}".format(name, statistics.mean(results), statistics.stdev(results)))
