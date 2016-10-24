"""
Homework 3


Data Description:
    Input the training and testing data and store it in an array. Training results in 284x31
    and Testing results in 284x31. The data entries
    consist of a first entry class label('1' for malignant and '-1' for benign) followed by 30
    breast cancer diagnostic measurements.
"""

import numpy as np
import os

raw_training_data_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'knn_data/knn_train.csv')
raw_testing_data_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'knn_data/knn_test.csv')

raw_training_data = np.loadtxt(raw_training_data_path, dtype=float, delimiter=',')
raw_testing_data = np.loadtxt(raw_testing_data_path, dtype=float, delimiter=',')


def get_data_answers(input_array):
    """Split off the first column answers and put in a dummy attribute of 1's in the first
     column.
     """
    input_array_split = np.split(input_array, [1], axis=1)
    data_features = np.array(input_array_split[1])
    length = data_features.shape[0]
    data_features = np.insert(data_features, 0, np.ones((1, length)), axis=1)
    answers = np.array(input_array_split[0])
    return data_features, answers


def get_by_row(answers, input_data):
    """Takes a column of input answers and an array of arrays of data and returns each answer,
    data set pair.
    """
    for row in np.concatenate((answers, input_data), axis=1):
        split_row = np.split(row, [1])
        answer = split_row[0][0]
        features = split_row[1]
        yield answer, features


def distance(vector_one, vector_two):
    """Calculates the distance between two numpy arrays."""
    return np.linalg.norm(vector_one - vector_two)


def _get_k_nearest(test_entry, training_answers, training_data):
    yield '_', float("infinity"), '_'
    for current_answer, current_data in get_by_row(training_answers, training_data):
        yield current_data, distance(test_entry, current_data), current_answer


def get_k_nearest(k, test_entry, training_answers, training_data):
    all_nearest = list(_get_k_nearest(test_entry, training_answers, training_data))
    all_nearest.sort(key=lambda l: l[1])
    return all_nearest[:k]


def knn_classifier(k, test_entry, training_answers, training_data):
    """Classifies a test entry using k nearest neighbor classification against training data."""
    k_nearest_so_far = get_k_nearest(k, test_entry, training_answers, training_data)
    class_sum = 0
    for entry in k_nearest_so_far:
        class_sum += entry[2]

    if class_sum > 0:
        return 1
    else:
        return -1


def pull_one_out(answers, input_data):
    """Takes a column of input answers and an array of arrays of data and returns each answer,
    data set pair along with the answer, data set arrays that result from having pulled those
    single entries out.
    """
    number_of_rows = input_data.shape[0]
    for index in range(number_of_rows):
        remaining_answers = np.concatenate((answers[:index], answers[index + 1:]), axis=0)
        remaining_data = np.concatenate((input_data[:index], input_data[index + 1:]), axis=0)
        yield answers[index], input_data[index], remaining_answers, remaining_data


def testing_k_values(training_answers, training_data, testing_data, testing_answers):
    """Measures performance using percentage error on leave-one-out cross validation using k
    nearest neighbors classification.
    """
    for k in range(1, 17, 2):
        training_errors = 0
        leave_one_out_errors = 0
        test_data_errors = 0

        # Training Error
        for data, answer in zip(training_data, training_answers):
            estimation = knn_classifier(k, data, training_answers, training_data)
            if estimation != answer:
                training_errors += 1

        # Cross Validation Error
        for verify_answer, verify_data, remaining_answers, remaining_data in pull_one_out(
                training_answers, training_data):
            estimation = knn_classifier(k, verify_data, remaining_answers, remaining_data)
            if estimation != verify_answer:
                leave_one_out_errors += 1

        # Test data error
        for data, answer in zip(testing_data, testing_answers):
            estimation = knn_classifier(k, data, training_answers, training_data)
            if estimation != answer:
                test_data_errors += 1

        yield k, training_errors, leave_one_out_errors, test_data_errors


def main():
    training_data, training_answers = get_data_answers(raw_training_data)
    testing_data, testing_answers = get_data_answers(raw_testing_data)
    for line in testing_k_values(training_answers, training_data, testing_data, testing_answers):
        print("{},{},{},{}".format(*line))


if __name__ == "__main__":
    main()
