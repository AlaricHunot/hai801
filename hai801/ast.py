import heapq
import copy

class Node:
    def __init__(self, id, heuristic_cost, total_cost, neighbors):
        self.id = id
        self.heuristic_cost = heuristic_cost
        self.total_cost = total_cost
        self.neighbors = neighbors

    def __eq__(self, other):
        return self.id == other.id

    def __hash__(self):
        return hash(self.id)

def find_solutions(graph, start, goal):
    solutions = []
    visited = set()
    open_set = {start.id: (start.total_cost, [start])}

    while open_set:
        current_id = min(open_set, key=lambda k: open_set[k][0])
        total_cost, current_path = open_set.pop(current_id)
        current_node = current_path[-1]

        if current_node == goal:
            solutions.append(current_path)

        visited.add(current_node)

        for neighbor_id, neighbor_cost in current_node.neighbors:
            next_node = next((node for node in graph if node.id == neighbor_id), None)
            if next_node:
                next_cost = current_node.total_cost + neighbor_cost
                next_path = copy.deepcopy(current_path)  # Créer une copie de current_path
                next_path.append(next_node)  # Ajouter next_node à la copie
                if next_node not in visited:
                    open_set[next_node.id] = (next_cost, next_path)

    return solutions

graph = [
    Node('a', 9, 0, [('b', 2), ('d', 3), ('c', 10)]),
    Node('b', 3, 0, [('a', 2), ('e', 2)]),
    Node('c', 5, 0, [('a', 10), ('d', 2), ('g', 2)]),
    Node('d', 6, 0, [('a', 3), ('c', 2), ('f', 4)]),
    Node('e', 8, 0, [('b', 3), ('f', 5), ('h', 10)]),
    Node('f', 4, 0, [('e', 5), ('d', 4), ('g', 5)]),
    Node('g', 2, 0, [('c', 2), ('f', 4), ('h', 1)]),
    Node('h', 0, 0, [])
]

start_node = next(node for node in graph if node.id == 'a')
goal_node = next(node for node in graph if node.id == 'h')

solutions = find_solutions(graph, start_node, goal_node)

if solutions:
    print("Solutions trouvées :")
    for solution in solutions:
        path = ' '.join(node.id for node in solution)
        print(path)
else:
    print("Aucune solution trouvée.")