"""HW 4 k means clustering algorithm.

    Implements k means clustering.
    Input data is 400 points in 2-dimensional space and is .csv format.
    The data and is randomly permuted after loading in order to randomize the initialization for k means.
"""

import os
import csv
import random
import math
import numpy as np
import pprint
import matplotlib.pyplot as plt

data_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'cluster-data-for-k-means.csv')
with open(data_path, 'r') as data_file:
    # Changed: list() "freezes" the row generator into a normal list
    data = list(csv.reader(data_file, delimiter=',', quoting=csv.QUOTE_NONNUMERIC))
random.shuffle(data)


def distance(point_one, point_two):
    """Calculates the Euclidean distance from point_one to point_two
    """
    return math.sqrt((point_two[0] - point_one[0]) ** 2 + (point_two[1] - point_one[1]) ** 2)


def index_of_closest_cluster(data_point, target_list):
    """Finds the index for a target in target_list that minimizes the distance to data_point
    """
    index_distances_pairs = []
    for index, target in enumerate(target_list):
        index_distances_pairs.append([index, distance(data_point, target)])
    index_distances_pairs.sort(key=lambda k: k[1])
    return index_distances_pairs[0][0]


def mean_of_cluster(list_of_points):
    """Calculates the center of the list of points
    """
    number_of_points = float(len(list_of_points))
    vector_total = [float(0), float(0)]
    for point in list_of_points:
        for index, component in enumerate(point):
            vector_total[index] += component
    return vector_total[0] / number_of_points, vector_total[1] / number_of_points


def new_clusters(old_cluster_means):
    """Assigns data points to individual clusters according to which old cluster mean is closest.
    :param old_cluster_means: List of centers for the previous clusters
    :return: new_cluster_means, new_cluster_list
    """
    # Changed: used the generator syntax
    new_cluster_means = [[] for _ in old_cluster_means]
    new_cluster_list = [[] for _ in old_cluster_means]
    for data_entry in data:
        new_cluster_list[index_of_closest_cluster(data_entry, old_cluster_means)].append(data_entry)
    for index, points_in_cluster in enumerate(new_cluster_list):
        new_cluster_means[index] = mean_of_cluster(points_in_cluster)
    return new_cluster_means, new_cluster_list


def square_distances(list_of_centers, list_of_clusters):
    """Calculates the sum of squared distances from the points in each cluster to the center of the cluster
    """
    for index in range(len(list_of_clusters)):
        for point in list_of_clusters[index]:
            yield (distance(point, list_of_centers[index])) ** 2


def sum_square_distances(list_of_centers, list_of_clusters):
    return sum(square_distances(list_of_centers, list_of_clusters))


def k_means_clusters(k, total_iterations):
    """Returns a list of [iteration, SSE] results for k means clustering along with the cluster list resulting from
    the last iteration.
    """
    # Changed: used in the inline array generator syntax
    # Seed the means
    current_means = [data[i] for i in range(min(k, len(data)))]
    performance_list = []  # Will contain entries: [iteration, SSE]
    current_cluster_list = None
    for iteration in range(total_iterations):
        current_means, current_cluster_list = new_clusters(current_means)
        performance_list.append([iteration, sum_square_distances(current_means, current_cluster_list)])
    return performance_list, current_cluster_list


def next_coordinates(points_in_cluster):
    x_coordinates, y_coordinates = np.split(points_in_cluster, [1], axis=1)
    return x_coordinates, y_coordinates


def plot_list(cluster_list):
    # Changed: Iter(..) was unusual.
    colors = ['red', 'orange', 'yellow', 'green', 'blue', 'black', 'grey', 'white', 'purple', 'pink']
    for i, cluster in enumerate(cluster_list):
        x, y = next_coordinates(cluster)
        yield plt.scatter(x, y, c=colors[i])


def generate_sse(k, repetitions=10):
    for _ in range(repetitions):
        random.shuffle(data)
        iteration_sse_list, _ = k_means_clusters(k, 7)
        yield iteration_sse_list[-1][1]


def find_smallest_sse(k):
    return min(generate_sse(k))


def generate_k_list(min_k, max_k):
    for k in range(min_k, max_k):
        yield k, find_smallest_sse(k)


def generate_sse_iterations(min_iterations, max_iterations):
    for iterations in range(min_iterations, max_iterations):
        yield iterations, min(generate_sse(3, iterations))


def main():
    """Currently runs the clusters algorithm over a number of iteretions then prints the total sum of squares
     error per iteration and plots the clustering achieved at the last iteration. Plot color iteration will
     run out causing an error if you increase the number of clusters past 10
    """
    iteration_sse_list, last_cluster_list = k_means_clusters(3, 7)
    print("Smallest: k - sse")
    pprint.pprint(sorted(list(generate_k_list(2, 10)), key=lambda k: k[1], reverse=True))
    plt.show(list(plot_list(last_cluster_list)))


if __name__ == '__main__':
    main()
