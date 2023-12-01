#include <iostream>
#include <climits>

using namespace std;

const int MAX_NODES = 100;
const int INF = INT_MAX;

// Function to find the node with the minimum distance value
int minDistance(int distance[], bool visited[], int numNodes) {
    int minDist = INF, minIndex = -1;
    for (int i = 0; i < numNodes; ++i) {
        if (!visited[i] && distance[i] < minDist) {
            minDist = distance[i];
            minIndex = i;
        }
    }
    return minIndex;
}

// Function to print the routing table
void printRoutingTable(int distance[], int source, int numNodes) {
    cout << "Routing Table for Node " << source << ":\n";
    cout << "Destination\tDistance\n";
    for (int i = 0; i < numNodes; ++i) {
        if (i != source) {
            cout << i << "\t\t" << distance[i] << "\n";
        }
    }
    cout << endl;
}

// Function to perform Link State Routing using Dijkstra's algorithm
void linkStateRouting(int graph[MAX_NODES][MAX_NODES], int source, int numNodes) {
    int distance[MAX_NODES];
    bool visited[MAX_NODES];

    // Initialize distance values and visited array
    for (int i = 0; i < numNodes; ++i) {
        distance[i] = INF;
        visited[i] = false;
    }

    // Distance from the source to itself is always 0
    distance[source] = 0;

    for (int count = 0; count < numNodes - 1; ++count) {
        int u = minDistance(distance, visited, numNodes);
        visited[u] = true;

        for (int v = 0; v < numNodes; ++v) {
            if (!visited[v] && graph[u][v] && distance[u] != INF && distance[u] + graph[u][v] < distance[v]) {
                distance[v] = distance[u] + graph[u][v];
            }
        }
    }

    // Print the routing table for each node
    for (int i = 0; i < numNodes; ++i) {
        if (i != source) {
            printRoutingTable(distance, i, numNodes);
        }
    }
}

int main() {
    int numNodes;

    // Input the number of nodes
    cout << "Enter the number of nodes: ";
    cin >> numNodes;

    // Input the adjacency matrix representing the weighted graph
    int graph[MAX_NODES][MAX_NODES];
    cout << "Enter the adjacency matrix (use INF for no direct connection):\n";
    for (int i = 0; i < numNodes; ++i) {
        for (int j = 0; j < numNodes; ++j) {
            cin >> graph[i][j];
        }
    }

    // Input the source node for Link State Routing
    int source;
    cout << "Enter the source node for Link State Routing: ";
    cin >> source;

    // Perform Link State Routing using Dijkstra's algorithm
    linkStateRouting(graph, source, numNodes);

    return 0;
}