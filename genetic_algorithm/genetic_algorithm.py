from math import exp, sin, fabs
import random


def func(x):
    # return exp(2*sin(5*x))+0.5*sin(x)
    # return sin(x / 2)
    return sin(x * 2) / 10 + x / 20


def get_rnd_in_range(a, b):
    return a + random.random() * b


def mutation(x_min, x_max):
    return x_min + get_rnd_in_range(x_min, x_max)


def inversion(x, eps=0.000001):
    if (get_rnd_in_range(0, 1) > 0.5):
        return x - eps

    return x + eps


def crossover(x, eps, x_min, x_max):
    # print(len(x))

    k = 99
    i = 0
    j = 0

    while (i < 8):
        j = i + 1
        while (j < 8):
            x[k] = (x[i] + x[j]) / 2
            k -= 1
            j += 1
        i += 1

    i = 0

    for i in range(8):
        x[k] = inversion(x[i], eps)
        k -= 1

        x[k] = inversion(x[i], eps)
        k -= 1

    i = 8

    while (i < k):
        x[i] = mutation(x_min, x_max)
        i += 1

    return x


def sort(x, y):
    i = 0
    j = 0

    while (i < 100):
        j = i + 1
        while (j < 100):
            if (fabs(y[j]) < fabs(y[i])):
                temp = y[i]
                y[i] = y[j]
                y[j] = temp
                temp = x[i]
                x[i] = x[j]
                x[j] = temp

            j += 1

        i += 1

    return [x, y]


def alg(x_min, x_max, eps=0.000001):
    population = []
    fitness = []
    iter = 0

    for i in range(100):
        population.append(mutation(x_min, x_max))
        fitness.append(func(population[i]))

    population, fitness = sort(population, fitness)

    iter += 1
    population = crossover(population, eps, x_min, x_max)

    for i in range(100):
        fitness[i] = func(population[i])

    population, fitness = sort(population, fitness)

    while (fabs(fitness[0]) > eps and iter < 20000):
        # print(fabs(fitness[0]))
        iter += 1
        population = crossover(population, eps, x_min, x_max)

        for i in range(100):
            fitness[i] = func(population[i])

        population, fitness = sort(population, fitness)

    return [population[0], fitness[0], iter]


x, y, iter = alg(0.0, 20.0, 0.000001)

print('x = {0}, y = {1}, iter = {2}'.format(x, y, iter))
