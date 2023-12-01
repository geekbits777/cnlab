#include <iostream>
#include <vector>

using namespace std;

const int INF = 999999; // Infinity as a large value

// Function to print the routing table
void printRoutingTable(vector<vector<int>> &routingTable, int numNodes)
{
     cout << "Node\tID\tDistance\tNext Node\n";
     for (int i = 0; i < numNodes; ++i)
     {
          cout << i << "\t";
          for (int j = 0; j < 3; ++j)
          {
               cout << routingTable[i][j] << "\t";
          }
          cout << endl;
     }
}

// Function to update the routing table based on distance vectors
void updateRoutingTable(vector<vector<int>> &routingTable, int node, int numNodes)
{
     for (int dest = 0; dest < numNodes; ++dest)
     {
          // Skip the node itself
          if (dest == node)
          {
               continue;
          }

          // If the distance through the current node is shorter, update the routing table
          if (routingTable[node][2] + routingTable[node][3 * dest] < routingTable[dest][2])
          {
               routingTable[dest][2] = routingTable[node][2] + routingTable[node][3 * dest];
               routingTable[dest][3] = node;
          }
     }
}

int main()
{
     int numNodes;

     // Input the number of nodes
     cout << "Enter the number of nodes: ";
     cin >> numNodes;

     // Input the adjacency matrix
     vector<vector<int>> adjacencyMatrix(numNodes, vector<int>(numNodes));
     cout << "Enter the adjacency matrix:\n";
     for (int i = 0; i < numNodes; ++i)
     {
          for (int j = 0; j < numNodes; ++j)
          {
               cin >> adjacencyMatrix[i][j];
          }
     }

     // Initialize the routing table
     vector<vector<int>> routingTable(numNodes, vector<int>(3 + 3 * numNodes));
     for (int i = 0; i < numNodes; ++i)
     {
          routingTable[i][0] = i; // Node
          routingTable[i][1] = i; // ID
          routingTable[i][2] = 0; // Distance
          routingTable[i][3] = i; // Next Node

          for (int j = 0; j < numNodes; ++j)
          {
               routingTable[i][3 * j + 4] = adjacencyMatrix[i][j]; // Distance vectors
          }
     }

     // Print the initial routing table
     cout << "Initial Routing Table:\n";
     printRoutingTable(routingTable, numNodes);

     // Iterate through the nodes and update the routing table
     for (int node = 0; node < numNodes; ++node)
     {
          updateRoutingTable(routingTable, node, numNodes);
     }

     // Print the updated routing table after 1 iteration
     cout << "\nUpdated Routing Table after 1 iteration:\n";
     printRoutingTable(routingTable, numNodes);

     return 0;
}