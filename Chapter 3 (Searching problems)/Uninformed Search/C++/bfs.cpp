#include <bits/stdc++.h>
using namespace std;

// Graph stored as adjacency matrix (2D vector).
// For unweighted graphs, use 1 to indicate an edge and -1 for no edge.
vector<int> bfs(const vector<vector<int>> &g, int s, int t)
{
    int n = (int)g.size();
    queue<int> q;
    vector<int> par(n, -1);
    vector<char> vis(n, 0);
    q.push(s);
    vis[s] = 1;
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        if (u == t)
        {
            vector<int> path;
            for (int x = u; x != -1; x = par[x])
                path.push_back(x);
            reverse(path.begin(), path.end());
            return path;
        }
        for (int v = 0; v < n; ++v)
        {
            if (g[u][v] != -1 && !vis[v])
            {
                vis[v] = 1;
                par[v] = u;
                q.push(v);
            }
        }
    }
    return {};
}

int main()
{
    // Node labels for printing
    vector<string> names = {"A", "B", "C", "D", "E", "F"};
    int n = (int)names.size();
    // Build adjacency matrix with -1 as no edge, 1 as edge
    vector<vector<int>> g(n, vector<int>(n, -1));
    auto add_edge = [&](int u, int v)
    { g[u][v] = 1; };
    add_edge(0, 1); // A->B
    add_edge(0, 2); // A->C
    add_edge(1, 3); // B->D
    add_edge(1, 4); // B->E
    add_edge(2, 5); // C->F
    add_edge(4, 5); // E->F

    auto path = bfs(g, 0, 5); // A to F
    for (size_t i = 0; i < path.size(); ++i)
    {
        if (i)
            cout << " ";
        cout << names[path[i]];
    }
    cout << "\n";
}
