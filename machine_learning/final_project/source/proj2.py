import os
import random

import numpy as np
from PIL import Image
from sklearn.cross_validation import train_test_split
from sklearn.utils.validation import check_consistent_length
from tensorflow.python.ops.rnn import bidirectional_rnn
from tensorflow.python.ops.rnn_cell import BasicLSTMCell


def convert_row_to_binary(row):
    for pixel in row:
        if pixel == 0:
            yield 0
        else:
            yield 1


def convert_to_binary(image):
    for row in image:
        yield list(convert_row_to_binary(row))


def load_image(filename):
    img = Image.open(filename)
    img.load()
    img.thumbnail((64, 64))
    return list(np.array(img.convert("L")))


def load_all_images(directory, category):
    for root, dirs, files in os.walk(directory):
        for file in files:
            try:
                image = load_image(os.path.join(root, file))
            except OSError:
                continue
            try:
                check_consistent_length(image)
                if len(image) != 64:
                    raise ValueError
            except ValueError:
                continue
            else:
                yield image, category


android_images = list(load_all_images('/Users/a5c/Desktop/training3/android', [0.0, 1.0]))
iphone_images = list(load_all_images('/Users/a5c/Desktop/training3/iphone', [1.0, 0.0]))
train, test = train_test_split(android_images + iphone_images)
data_train, labels_train = zip(*train)
data_test, labels_test = zip(*test)
data_train, labels_train, data_test, labels_test = \
    np.array(data_train), np.array(labels_train), np.array(data_test), np.array(labels_test)

'''
A Bidirectional Recurrent Neural Network (LSTM) implementation example using TensorFlow library.
This example is using the MNIST database of handwritten digits (http://yann.lecun.com/exdb/mnist/)
Long Short Term Memory paper: http://deeplearning.cs.cmu.edu/pdfs/Hochreiter97_lstm.pdf
Author: Aymeric Damien
Project: https://github.com/aymericdamien/TensorFlow-Examples/
'''

import tensorflow as tf

# Import MINST data

dataset = tf.placeholder(tf.float16)


'''
To classify images using a bidirectional reccurent neural network, we consider
every image row as a sequence of pixels. Because MNIST image shape is 28*28px,
we will then handle 28 sequences of 28 steps for every sample.
'''

# Parameters
learning_rate = 0.001
display_step = 10

# Network Parameters
n_input = 64  # MNIST data input (img shape: 28*28)
n_steps = 64  # timesteps
n_hidden = 64  # hidden layer num of features
n_classes = 2  # MNIST total classes (0-9 digits)

# tf Graph input
x = tf.placeholder("float", [None, n_steps, n_input])
y = tf.placeholder("float", [None, n_classes])

# Define weights
weights = {
    # Hidden layer weights => 2*n_hidden because of forward + backward cells
    'hidden': tf.Variable(tf.random_normal([n_input, 2 * n_hidden])),
    'out': tf.Variable(tf.random_normal([2 * n_hidden, n_classes]))
}
biases = {
    'hidden': tf.Variable(tf.random_normal([2 * n_hidden])),
    'out': tf.Variable(tf.random_normal([n_classes]))
}


def bi_rnn(x, weights, biases):
    # Prepare data shape to match `bidirectional_rnn` function requirements
    # Current data input shape: (batch_size, n_steps, n_input)
    # Permuting batch_size and n_steps
    x = tf.transpose(x, [1, 0, 2])
    # Reshape to (n_steps*batch_size, n_input)
    x = tf.reshape(x, [-1, n_input])
    # Split to get a list of 'n_steps' tensors of shape (batch_size, n_hidden)
    x = tf.split(0, n_steps, x)

    # Define lstm cells with tensorflow
    # Forward direction cell
    lstm_fw_cell = BasicLSTMCell(n_hidden, forget_bias=1.0)
    # Backward direction cell
    lstm_bw_cell = BasicLSTMCell(n_hidden, forget_bias=1.0)

    # Get lstm cell output
    outputs = bidirectional_rnn(lstm_fw_cell, lstm_bw_cell, x, dtype=tf.float32)

    # Linear activation, using rnn inner loop last output
    return tf.matmul(outputs[-1], weights['out']) + biases['out']


pred = bi_rnn(x, weights, biases)

# Define loss and optimizer
cost = tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(pred, y))
optimizer = tf.train.AdamOptimizer(learning_rate=learning_rate).minimize(cost)

# Evaluate model
correct_pred = tf.equal(tf.argmax(pred, 1), tf.argmax(y, 1))
accuracy = tf.reduce_mean(tf.cast(correct_pred, tf.float32))

# Initializing the variables
init = tf.initialize_all_variables()

# Launch the graph
with tf.Session() as sess:
    sess.run(init)
    step = 1
    training = list(zip(data_train, labels_train))
    # Keep training until reach max iterations
    for i in range(30):
        random.shuffle(training)
        batch_x, batch_y = zip(*training[:15])
        # Run optimization op (backprop)
        sess.run(optimizer, feed_dict={x: batch_x, y: batch_y})
        if step % display_step == 0:
            # Calculate batch accuracy
            acc = sess.run(accuracy, feed_dict={x: batch_x, y: batch_y})
            # Calculate batch loss
            loss = sess.run(cost, feed_dict={x: batch_x, y: batch_y})
            print("Iter " + str(step) + ", Minibatch Loss= " +
                  "{:.6f}".format(loss) + ", Training Accuracy= " +
                  "{:.5f}".format(acc))
        step += 1
    print("Optimization Finished!")

    # Calculate accuracy for 128 mnist test images
    test_len = len(data_test)
    test_data_tf = data_test
    test_label_tf = labels_test
    print("Testing Accuracy:",
          sess.run(accuracy, feed_dict={x: test_data_tf, y: test_label_tf}))
