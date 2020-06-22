#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <list>

using namespace std;

class Graph {
    int V;
    list<int> *adj;
    void dfs(int v, bool visited[]);
public:
    Graph(int v);
    ~Graph();
    void add_edges(int v, int w);
    void connected_components();
};

Graph::Graph(int v)
{
    V = v;
    adj = new list<int>[v];
}

Graph::~Graph()
{
    delete[] adj;
}

void Graph::add_edges(int v, int w)
{
    adj[v].push_back(w);
    adj[w].push_back(v);
}

void Graph::dfs(int v, bool visited[])
{
    visited[v] = true;
    cout << v << " ";
    list<int>::iterator it;
    for (it = adj[v].begin(); it != adj[v].end(); it++) {
        if (!visited[*it])
            dfs(*it, visited);
    }
}

void Graph::connected_components()
{
    bool *visited = new bool[V];
    for (int v = 0; v < V; v++)
        visited[v] = false;
    for (int v = 0; v < V; v++) {
        if (!visited[v]) {
            dfs(v, visited);
            cout << "\n";
        }
    }
    delete[] visited;
}

int main()
{
    Graph g(5);
    g.add_edges(0, 1);
    g.add_edges(1, 2);
    g.add_edges(3, 4);
    g.connected_components();
}
