#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
using namespace std;


class Graph {
public:
    int V; 
    vector<vector<int>> adjList;

public:
    Graph(int vertices) : V(vertices) {
        adjList.resize(V);
    }

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
    }

    void BFS(int startVertex) {
        vector<bool> visited(V, false);
        queue<int> q;
        unordered_set<int> seen;

        q.push(startVertex);
        seen.insert(startVertex);

        while (!q.empty()) {
            int currentVertex = q.front();
            q.pop();
            cout << currentVertex << " ";
            visited[currentVertex] = true;

            for (int i = 0; i < adjList[currentVertex].size(); ++i) {
                int neighbor = adjList[currentVertex][i];
                if (!seen.count(neighbor)) {
                    q.push(neighbor);
                    seen.insert(neighbor);
                }
            }
        }
    }
};

int main() {
    Graph g(6);

    g.addEdge(0, 1);//edges
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(3, 5);
    g.addEdge(4, 5);
    g.addEdge(1, 4);
    g.addEdge(2, 4);
    g.addEdge(3, 4);


    cout << "BFS Traversal from vertex 0: ";
    g.BFS(0);

    return 0;
}
