"""
Decision Tree for Homework 3

    Input the training and testing data and store it in an array. Training results in 124x7
    and Testing results in 432x7. The data entries
    consist of a first entry class label('1' for 'x_5=1 and x_0 != x_1' and '0' otherwise) followed by 6 feature values
    of x_0 - x_5.
"""

import numpy as np
import os
import math

raw_training_data_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'DT_data/monks-1-train.csv')
raw_testing_data_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'DT_data/monks-1-test.csv')
raw_training_data = np.loadtxt(raw_training_data_path, dtype=int, delimiter=',')
raw_testing_data = np.loadtxt(raw_testing_data_path, dtype=int, delimiter=',')


def get_data_answers(input_array):
    """split off the first column answers."""
    input_array_split = np.split(input_array, [1], axis=1)
    data_features = np.array(input_array_split[1])
    answers = np.array(input_array_split[0])
    return answers, data_features


def get_by_row(answers, input_data):
    """Takes a column of input answers and an array of arrays of data and returns each answer,
    data set pair."""
    for row in np.concatenate((answers, input_data), axis=1):
        split_row = np.split(row, [1])
        answer = split_row[0][0]
        features = split_row[1]
        yield answer, features


def information_gain(x, y, z, w, old_entropy):
    """ Calculates information gain based on a binary split that separates the data in to two bins that would
    represent the next nodes. The number of positive (negative) classes in bins one and two are given by x (y)
    and z (w) respectively."""
    frac_one = float(x + y) / float(x + y + z + w)  # fraction of data falling in bin one
    frac_two = 1 - frac_one  # fraction of data falling in bin two
    frac_pos_one = float(x) / float(x + y)  # fraction of bin one that are of positive class
    frac_neg_one = float(y) / float(x + y)  # fraction of bin one that are of negative class
    frac_pos_two = float(z) / float(z + w)  # fraction of bin two that are of positive class
    frac_neg_two = float(w) / float(z + w)  # fraction of bin two that are of negative class
    if frac_pos_one == 0:
        bin_one_entropy = -frac_neg_one * math.log(frac_neg_one, 2)
    elif frac_neg_one == 0:
        bin_one_entropy = -frac_pos_one * math.log(frac_pos_one, 2)
    else:
        bin_one_entropy = -frac_pos_one * math.log(frac_pos_one, 2) \
                          - frac_neg_one * math.log(frac_neg_one, 2)
    if frac_pos_two == 0:
        bin_two_entropy = -frac_neg_two * math.log(frac_neg_two, 2)
    elif frac_neg_two == 0:
        bin_two_entropy = -frac_pos_two * math.log(frac_pos_two, 2)
    else:
        bin_two_entropy = -frac_pos_two * math.log(frac_pos_two, 2) \
                          - frac_neg_two * math.log(frac_neg_two, 2)
    new_entropy = frac_one * bin_one_entropy + frac_two * bin_two_entropy
    info_gain = old_entropy - new_entropy
    return info_gain, bin_one_entropy, bin_two_entropy


def split_performance(node_answers, node_data, node_entropy, split):
    """ Divides the data that remains at a given node and splits it in two groups according to an attribute value
    test. The test to be perfomed is encoded in a tuple n,m meaning test if x_n == m. """
    split_index = split[0]
    split_value = split[1]
    bin_one_positives = 0
    bin_one_negatives = 0
    bin_two_positives = 0
    bin_two_negatives = 0
    for answer, data in get_by_row(node_answers, node_data):
        if data[split_index] == split_value:
            if answer == 1:
                bin_one_positives += 1
            else:
                bin_one_negatives += 1
        else:
            if answer == 1:
                bin_two_positives += 1
            else:
                bin_two_negatives += 1
    if bin_one_positives + bin_one_negatives == 0 or bin_two_positives + bin_two_negatives == 0:
        performance = 0
        bin_one_entropy = '_'
        bin_two_entropy = '_'
    else:
        performance, bin_one_entropy, bin_two_entropy = information_gain(
            bin_one_positives, bin_one_negatives, bin_two_positives, bin_two_negatives, node_entropy)
    return [performance, bin_one_entropy, bin_two_entropy]


def binary_trunk(training_answers, training_data):
    """ Determines the binary trunk of a decision tree that maximizes information gain over all possible trunks
    with the condition that the binary decision is formed by testing whether some chosen feature has a chosen
    value."""
    base_positives = 0
    for answer in training_answers:
        if answer == 1:
            base_positives += 1
    frac_pos_base = float(base_positives) / float(training_answers.shape[0])  # Fraction of positive classes at base
    frac_neg_base = 1 - frac_pos_base  # Fraction of negative classes at the base
    base_entropy = -frac_pos_base * math.log(frac_pos_base, 2) - frac_neg_base * math.log(frac_neg_base, 2)
    values_list = [[1, 2], [1, 2], [1], [1, 2], [1, 2], [1]]
    best_split_so_far = [0, 1, 0]  # [feature_index,feature_value,info_gain] for greatest info_gain split so far
    for feature_index in range(6):
        for feature_value in values_list[feature_index]:
            this_split = [feature_index, feature_value]
            this_gain = split_performance(training_answers, training_data, base_entropy, this_split)[0]
            print [feature_index, feature_value, this_gain]
            if this_gain > best_split_so_far[2]:
                best_split_so_far = [feature_index, feature_value, this_gain]
    return best_split_so_far


def main():
    training_answers, training_data = get_data_answers(raw_training_data)
    # holdout_answers, holdout_data = get_data_answers(raw_testing_data)
    trunk = binary_trunk(training_answers, training_data)
    print trunk


if __name__ == '__main__':
    main()
