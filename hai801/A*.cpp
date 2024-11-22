#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct Node {
    char id;
    int heuristicCost;
    vector<pair<Node*, int>> neighbors;
    Node* parent; // Ajout du membre parent

    Node(char id, int heuristicCost) : id(id), heuristicCost(heuristicCost), parent(nullptr) {} // Initialisation de parent à nullptr
};

struct Compare {
    bool operator()(const pair<int, Node*>& a, const pair<int, Node*>& b) {
        return a.first > b.first; // Comparaison pour une file de priorité minimale
    }
};

vector<Node*> findSolution(const vector<Node>& graph, Node* start, Node* goal) {
    vector<Node*> solution;
    unordered_map<Node*, int> totalCostMap;
    priority_queue<pair<int, Node*>, vector<pair<int, Node*>>, Compare> openSet;

    openSet.push({start->heuristicCost, start});
    totalCostMap[start] = 0;

    while (!openSet.empty()) {
        auto [currentPriority, current] = openSet.top();
        openSet.pop();

        if (current == goal) {
            // Reconstruire le chemin jusqu'au nœud de départ
            while (current) {
                solution.insert(solution.begin(), current);
                current = current->parent;
            }
            break;
        }

        for (const auto& [neighbor, cost] : current->neighbors) {
            int nextCost = totalCostMap[current] + cost;
            if (!totalCostMap.count(neighbor) || nextCost < totalCostMap[neighbor]) {
                totalCostMap[neighbor] = nextCost;
                openSet.push({nextCost + neighbor->heuristicCost, neighbor});
                neighbor->parent = current; // Mise à jour du parent pour le chemin optimal
            }
        }
    }

    return solution;
}

int main() {
    // Définir le graphe et les nœuds de départ et d'arrivée
    vector<Node> graph = {
        Node('a', 9),
        Node('b', 3),
        Node('c', 5),
        Node('d', 6),
        Node('e', 8),
        Node('f', 4),
        Node('g', 2),
        Node('h', 0)
    };

    // Ajouter les voisins pour chaque nœud
    graph[0].neighbors = {{&graph[1], 2}, {&graph[3], 3}, {&graph[2], 10}};
    graph[1].neighbors = {{&graph[0], 2}, {&graph[4], 2}};
    graph[2].neighbors = {{&graph[0], 10}, {&graph[3], 2}, {&graph[6], 2}};
    graph[3].neighbors = {{&graph[0], 3}, {&graph[2], 2}, {&graph[5], 4}};
    graph[4].neighbors = {{&graph[1], 3}, {&graph[5], 5}, {&graph[7], 10}};
    graph[5].neighbors = {{&graph[4], 5}, {&graph[3], 4}, {&graph[6], 5}};
    graph[6].neighbors = {{&graph[2], 2}, {&graph[5], 4}, {&graph[7], 1}};
    graph[7].neighbors = {}; // No neighbors for node 'h'

    Node* startNode = &graph[0]; // Nœud de départ (a)
    Node* goalNode = &graph[7]; // Nœud d'arrivée (h)

    if (startNode && goalNode) {
        vector<Node*> solution = findSolution(graph, startNode, goalNode);

        if (solution.empty()) {
            cout << "Aucune solution trouvée." << endl;
        } else {
            cout << "Solution trouvée :" << endl;
            for (const Node* node : solution) {
                cout << node->id << " ";
            }
            cout << endl;
        }
    } else {
        cout << "Impossible de trouver le nœud de départ ou le nœud cible." << endl;
    }

    return 0;
}