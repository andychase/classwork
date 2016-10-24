""" HW 4 Markov Decision Process HW4 Markov Decision Process optimal policy calculator.

    Data Input:
        Text file describing the MDP. First line gives two integers n and m specifying the number of states
        and actions respectively. After the first line there will be a blank line and then a sequence of m nxn matrices
        (each separated by a blank line) that give the transition probabilities for each action. The ith matrix gives
        the probabilities for transitioning using the ith action. After the final transition matrix there will be a
        blank line followed by a row of n real numbers. The ith real number specifies the reward for the ith state.

    Global Variables:
        discount_factor (factor that next step rewards are mutiplied by, simulates expected possible death)
        total_states (integer n from above)
        total_actions (integer m from above)
        transition_matrix_list (list of numpy float arrays giving transition matrices from above)
        reward_list (list of float rewards from above)
  """
import pprint

import numpy as np
import os
import csv
import copy

MDP_path = os.path.join(os.path.dirname(os.path.abspath(__file__)), 'test-data-for-MDP.txt')
transition_matrix_list = []
with open(MDP_path, 'r') as text_file:
    reader = csv.reader(text_file, skipinitialspace=True, delimiter=' ', quoting=csv.QUOTE_NONNUMERIC)

    total_states, total_actions = [int(entry) for entry in next(reader)]
    next(reader)
    for action_number in range(total_actions):
        transition_matrix = []
        for row in range(total_states):
            transition_matrix.append(next(reader))
        transition_matrix_list.append(np.array(transition_matrix))
        next(reader)
    reward_list = np.array(next(reader))


def expected_next_rewards(old_utility_list, current_state):
    for action in range(total_actions):
        yield [old_utility_list.dot(transition_matrix_list[action][current_state]), action]


def distance(vector_one, vector_two):
    return np.linalg.norm(vector_one - vector_two)


def utility_update(old_utility_list, discount_factor):
    """ Takes the current utility list and updates the utilities according to the formula:
        u_{next}[s] = R[s] + gamma*max_{action a}(Sum_{states s'}T[a][s][s']u[s']).
        This is where gamma = discount_factor, u is the utility tuple, R is the reward tuple,
        and T = transition_matrix_list. The sum is calculated using the function expected_next_reward().
    """
    new_utility_list = np.array([0.0] * len(old_utility_list))
    for state in range(total_states):
        new_utility_list[state] = reward_list[state] + \
                                  discount_factor * max(expected_next_rewards(old_utility_list, state),
                                                        key=lambda k: k[0])[0]
    norm_of_change = distance(old_utility_list, new_utility_list)
    return new_utility_list, norm_of_change


def utility_calculator(epsilon, discount_factor):
    utility_list = np.array(copy.copy(reward_list))
    threshold = epsilon * (1 - discount_factor) ** 2 / (2 * discount_factor ** 2)
    change = 2 * threshold
    while change > threshold:
        utility_list, change = utility_update(utility_list, discount_factor)
    return utility_list


def policy_calculator(final_utility):
    """ Determines the optimal policy given a utility function by finding for any starting state the action that
        maximizes the next likely utility.
        Returns a policy list the i_th entry of which provides the optimal action to take from state i.
    """
    policy_list = []
    for state in range(total_states):
        policy_list.append(max(expected_next_rewards(final_utility, state), key=lambda k: k[0])[1])
    return policy_list


def main():
    final_utility = utility_calculator(1E-10, 0.9)
    pprint.pprint(final_utility.tolist())
    pprint.pprint(policy_calculator(final_utility))


if __name__ == '__main__':
    main()
