import matplotlib.pyplot as plt
import numpy as np
from math import sin, log, exp
import time

X_MIN = -5
X_MAX = 5
K = 2.8
# EPS = 0.0000000001
EPS = 0.0001

plt.rcParams["figure.figsize"] = [7.50, 3.50]
plt.rcParams["figure.autolayout"] = True

fig = plt.figure()
ax = fig.gca()
fig.show()


def search_min(t):
    prev_x = get_next_rnd_value()
    line = draw_value(prev_x)

    while t > EPS:
        curr_x = get_next_rnd_value()
        prev_y = func(prev_x)
        curr_y = func(curr_x)

        if (curr_y <= prev_y or should_update_value(curr_y, prev_y, t)):
            prev_x = curr_x
            line = draw_value(curr_x, line)

        t = next_t(t)


def func(x):
    return sin(x * 2) / 10 + x / 20


def get_next_rnd_value():
    return np.random.uniform(X_MIN, X_MAX)


def get_curr_prob(curr, prev, t):
    return exp((prev - curr) / t)


def should_update_value(curr, prev, t):
    return get_curr_prob(curr, prev, t) > np.random.uniform(0, 1)


def draw_value(x, line=None):
    if (line):
        line.remove()
    line = ax.axvline(x=x, color='b', label='curr_x')
    fig.canvas.draw()
    plt.pause(0.001)
    return line


def next_t(t):
    return t / log(1 + K)


def add_func():
    x_grid = np.arange(X_MIN, X_MAX, 0.01)
    y_grid = [func(x) for x in x_grid]

    ax.plot(x_grid, y_grid)


t = 100

add_func()
search_min(t)
time.sleep(100)
