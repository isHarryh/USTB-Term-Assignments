import pandas as pd
import math
import matplotlib.pyplot as plt
import numpy as np


def read_data(file_path):
    # data = pd.read_table(file_path, header=None, skiprows=7, sep="\s+")
    data = pd.read_csv(file_path, header=None, skiprows=7)

    return data


def split_data(data):
    data = data.values
    positive_data = data[data[:, 2] == 1.0][:, 0]
    negative_data = data[data[:, 2] != 1.0][:, 0]
    return positive_data, negative_data


def parzen(a, x):
    hn = 0.2
    r = sum(1 / (2 * hn) if abs(x - xi) <= hn / 2.0 else 0 for xi in a)
    return r / len(a)


def knn1d(a, x):
    k = int(math.sqrt(len(a)))
    distances = np.abs(a - x)
    distances.sort()
    V = 2 * distances[k]
    px = k / (len(a) * V)
    return px


def plot_density_functions(data):
    fig, axes = plt.subplots(1, 2)
    fig.suptitle("Density Estimation Methods")

    x_values = np.arange(-3.09, 3.19, 0.01)

    for ax, method, estimator in zip(
        axes, ["Parzen Window", "K-Neighbor Estimation"], [parzen, knn1d]
    ):
        density_values = [estimator(data, x) for x in x_values]
        ax.plot(x_values, density_values)
        ax.set_title(method)

    plt.show()


if __name__ == "__main__":
    file_path = "banana.dat"
    data = read_data(file_path)
    positive_data, negative_data = split_data(data)

    plot_density_functions(positive_data)
