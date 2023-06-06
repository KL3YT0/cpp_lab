import sys
import numpy as np
from numpy.random import choice as np_choice


class AntColony(object):
    def __init__(self, distances, num_ants, num_interations, decay, alpha=1, beta=1):

        self.distances = distances
        self.pheromone = np.ones(self.distances.shape) * 0.2
        self.all_city = range(len(distances))
        self.num_ants = num_ants
        self.num_interations = num_interations
        self.decay = decay
        self.alpha = alpha
        self.beta = beta

    def run(self):
        shortest_way = None
        all_time_shortest_way = ("route", np.inf)
        for i in range(self.num_interations):
            all_route = self.gen_all_route()
            self.distribution_pheromone(
                all_route, self.num_ants, shortest_way=shortest_way)
            shortest_way = min(all_route, key=lambda x: x[1])

            if (shortest_way[1] < all_time_shortest_way[1]):
                all_time_shortest_way = shortest_way
            self.pheromone * self.decay 
        
        return all_time_shortest_way

    def distribution_pheromone(self, all_route, num_ants, shortest_way):
        sorted_way = sorted(all_route, key=lambda x: x[1])
        for way, dist in sorted_way[:num_ants]:
            for move in way:
                self.pheromone[move] += 1/self.distances[move]

    def gen_path_dist(self, way):
        total_distance = 0
        for l in way:
            total_distance += self.distances[l]
        return total_distance

    def gen_all_route(self):
        all_route = []
        for i in range(self.num_ants):
            way = self.gen_way(0)
            all_route.append((way, self.gen_path_dist(way)))

        return all_route

    def gen_way(self, start):
        way = []
        visited = set()
        visited.add(start)
        prev = start
        for i in range(len(self.distances)-1):
            move = self.pick_move(
                self.pheromone[prev], self.distances[prev], visited)
            way.append((prev, move))
            prev = move
            visited.add(move)
        way.append((prev, start))
        return way

    def pick_move(self, pheromone, dist, visited):
        pheromone = np.copy(pheromone)
        pheromone[list(visited)] = 0

        choice = pheromone ** self.alpha * ((1.0/dist) ** self.beta)
        
        norm_choice = choice / choice.sum()

        move = np_choice(self.all_city, 1, p=norm_choice)[0]
        return move


def greedy(distances):
    curr_vertex = 0
    way = []

    not_visited = []

    for i in range(len(distances)):
        not_visited.append(i)

    visited = [0]
    not_visited.remove(0)

    
    while (len(not_visited) > 0):
        next_vertex = not_visited[0]
        local_optimum = distances[curr_vertex, next_vertex]

        for vertex in not_visited:
            if (distances[curr_vertex, vertex] < local_optimum):
                local_optimum = distances[curr_vertex, vertex]
                next_vertex = vertex

        way.append((curr_vertex, next_vertex))
        curr_vertex = next_vertex
        visited.append(curr_vertex)
        not_visited.remove(curr_vertex)

    way.append((curr_vertex, 0))

    l = 0

    for p in way:
        l += distances[p[0], p[1]]

    return [way, l]

# Входные данные
np.random.seed(7)
distances = np.random.randint(1, 50, size=(20, 20))

distances = np.array(
[
    [0,  2,  30, 9,  1],
    [4,  0,  47, 7,  7],
    [31, 33, 0,  33, 36],
    [20, 13, 16, 0,  28],
    [9,  36, 22, 22, 0]
])

# 0 2 30 9 1
# 4 0 47 7 7
# 31 33 0 33 36
# 20 13 16 0 28
# 9 36 22 22 0

i = 0
j = 0
# изменнение главное диагонали, чтобы нельзя было пройти из города в тот же город
for p in range(len(distances)):
    distances[i][j] = 9999
    i += 1
    j += 1


ant_colony = AntColony(distances, 5, 100, 0.95, alpha=1, beta=2)

way1, l1 = ant_colony.run()

way1_view = []

for v in way1:
    way1_view.append((v[0] + 1, v[1] + 1))

print('Муравьиный алгоритм :\n маршрут: {0} \n расстояние: {1}'.format(way1_view, l1))

way2, l2 = greedy(distances)

way2_view = []

for v in way2:
    way2_view.append((v[0] + 1, v[1] + 1))

print('Жадный алгоритм :\n маршрут: {0} \n расстояние: {1}'.format(way2_view, l2))