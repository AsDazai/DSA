#include <iostream>
#include <vector>

using namespace std;

class Graph {
private:
    int numVertices;
    vector<vector<int>> adjMatrix;

public:
    Graph(int numVertices) : numVertices(numVertices) {
        adjMatrix.resize(numVertices, vector<int>(numVertices, 0));
    }

    void addEdge(int src, int dest) {
        adjMatrix[src][dest] = 1;
        adjMatrix[dest][src] = 1; // Uncomment for undirected graph
    }

    void printGraph() {
        cout << "Adjacency Matrix:" << endl;
        for (int i = 0; i < numVertices; ++i) {
            for (int j = 0; j < numVertices; ++j) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    void DFSRecursive(int startVertex, vector<bool>& visited) {
        visited[startVertex] = true;
        cout << startVertex << " ";

        for (int i = 0; i < numVertices; ++i) {
            if (adjMatrix[startVertex][i] && !visited[i]) {
                DFSRecursive(i, visited);
            }
        }
    }

    void DFSNonRecursive(int startVertex) {
        vector<bool> visited(numVertices, false);
        vector<int> stack;

        visited[startVertex] = true;
        stack.push_back(startVertex);
        cout << startVertex << " ";

        while (!stack.empty()) {
            int currentVertex = stack.back();
            stack.pop_back();

            for (int i = 0; i < numVertices; ++i) {
                if (adjMatrix[currentVertex][i] && !visited[i]) {
                    visited[i] = true;
                    cout << i << " ";
                    stack.push_back(i);
                }
            }
        }
    }
};

int main() {
    Graph graph(5);
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 3);
    graph.addEdge(1, 4);

    graph.printGraph();

    cout << "DFS Recursive: ";
    vector<bool> visited(5, false);
    graph.DFSRecursive(0, visited);
    cout << endl;

    cout << "DFS Non-Recursive: ";
    graph.DFSNonRecursive(0);
    cout << endl;

    return 0;
}
