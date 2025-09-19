import numpy as np


def sigmoid(x):
    return 1 / (1 + np.exp(-x))


x = np.array([200, 17])

w1_1 = np.array([1, 2])
b1_1 = np.array([-1])
z1_1 = np.dot(w1_1, x) + b1_1
a1_1 = sigmoid(z1_1[0])

w1_2 = np.array([-3, 4])
b1_2 = np.array([1])
z1_2 = np.dot(w1_2, x) + b1_2
a1_2 = sigmoid(z1_2[0])

w1_3 = np.array([5, -6])
b1_3 = np.array([2])
z1_3 = np.dot(w1_3, x) + b1_3
a1_3 = sigmoid(z1_3[0])

a1 = np.array([a1_1, a1_2, a1_3])

w2_1 = np.array([-7, 8, 9])
b2_1 = np.array([2])
z2_1 = np.dot(w2_1, a1) + b2_1
a2_1 = sigmoid(z2_1[0])

a2 = np.array([a2_1])
