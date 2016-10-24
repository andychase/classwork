"""
Homework 2


Data Description:
    Input the training and testing data and store it in an array. Training results in 1400x257
    and Testing results in 800x257. Each set is equally divided between classes. The data classes are
    16x16 digital images of hand written characters (either a '4' or a '9'). Each row has the answer
    in it as the last entry: '0' (meaning the digit was a 4) or a '1' (meaning the digit was a '9').
    Randomly permute the rows upon loading so that the classes are mixed randomly in the data.
"""

import numpy as np

raw_training_data = np.random.permutation(np.loadtxt('usps-4-9/usps-4-9-train.csv', dtype=float, delimiter=','))
raw_testing_data = np.random.permutation(np.loadtxt('usps-4-9/usps-4-9-test.csv', dtype=float, delimiter=','))


def get_data_answers(input_array):
    """Pop off the last column answers and put in a dummy attribute of 1's in the first column."""
    input_array_split = np.split(input_array, [-1], axis=1)
    data = np.array(input_array_split[0])
    length = data.shape[0]
    data = np.insert(data, 0, np.ones((1, length)), axis=1)
    answers = np.array(input_array_split[1])
    return data, answers


def g(weight, data):
    """Calculates the logistic function."""
    try:
        return 1.0 / (1.0 + np.math.exp(-weight.transpose().dot(data)))
    except OverflowError:
        return 0


def l(weight, data, answer):
    if answer == 1:
        return -np.math.log10(g(weight, data))
    else:
        return -np.math.log10(1 - g(weight, data))


def vector_length(w):
    return np.math.sqrt(sum(i ** 2 for i in w))


def get_by_row(answers, input_data):
    """Takes a column of input answers and an array of arrays of data and returns each answer, data set pair."""
    for row in np.concatenate((answers, input_data), axis=1):
        split_row = np.split(row, [1])
        answer = split_row[0][0]
        data = split_row[1]
        yield answer, data


def print_results(weight, answers, data_rows, prefix):
    """Find the accuracy of the weight vector using answers and data_rows and print it."""
    correct = 0
    for answer, data in get_by_row(answers, data_rows):
        if abs(answer - g(weight, data)) < 0.5:
            correct += 1
    print("{},{}".format(prefix, float(correct) / answers.shape[0]))


def batch_learn(input_data, answers, learning_rate, n, regularization):
    """Learns a value of the w weight vector in a logistic regression model
    using gradient descent on input data running a batch of input data followed by an update in w.
    :param regularization:
    :param input_data: input data numpy array
    :param answers: input answers
    :param n: iterations
    :param learning_rate: learning rate (lambda)
    :return: proposed weight vector
    """
    input_data_length = input_data.shape[1]
    weight = np.zeros(input_data_length)
    for _ in range(1, n):
        accumulate = np.zeros(input_data_length)
        for answer, data in get_by_row(answers, input_data):
            prediction = g(weight, data)
            error = answer - prediction
            accumulate += (error * data) - weight.dot(regularization)
        weight += accumulate * learning_rate
    return weight


def test_different_learning_rates(training_data, answers, testing_data_answers, testing_data):
    learning_rate = 1 * 10 ** -9
    for r in range(-3, 10):
        regular = 10**r
        weight_vector = batch_learn(training_data, answers, learning_rate, 100, regular)
        print_results(weight_vector, testing_data_answers, testing_data, "{}".format(regular))


def main():
    training_data, training_data_answers = get_data_answers(raw_training_data)
    testing_data, testing_data_answers = get_data_answers(raw_testing_data)

    test_different_learning_rates(training_data, training_data_answers, testing_data_answers, testing_data)


if __name__ == "__main__":
    main()
