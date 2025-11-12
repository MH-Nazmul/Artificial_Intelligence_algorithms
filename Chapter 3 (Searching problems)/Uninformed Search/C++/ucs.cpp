#include <bits/stdc++.h>
using namespace std;

// Uniform Cost Search on adjacency matrix with non-negative weights.
// -1 indicates no edge.
pair<vector<int>, int> ucs(const vector<vector<int>> &g, int s, int t)
{
    int n = (int)g.size();
    using T = pair<int, int>; // (cost,node)
    priority_queue<T, vector<T>, greater<T>> pq;
    pq.push({0, s});
    vector<int> dist(n, INT_MAX), par(n, -1);
    dist[s] = 0;
    vector<char> vis(n, 0);
    while (!pq.empty())
    {
        auto [c, u] = pq.top();
        pq.pop();
        if (vis[u])
            continue;
        if (u == t)
        {
            vector<int> path;
            for (int x = u; x != -1; x = par[x])
                path.push_back(x);
            reverse(path.begin(), path.end());
            return {path, c};
        }
        vis[u] = 1;
        for (int v = 0; v < n; ++v)
        {
            int w = g[u][v];
            if (w != -1)
            {
                int ng = dist[u] + w;
                if (ng < dist[v])
                {
                    dist[v] = ng;
                    par[v] = u;
                    pq.push({ng, v});
                }
            }
        }
    }
    return {{}, INT_MAX};
}

int main()
{
    vector<string> names = {"A", "B", "C", "D"};
    int n = (int)names.size();
    vector<vector<int>> g(n, vector<int>(n, -1));
    auto add_edge = [&](int u, int v, int w)
    { g[u][v] = w; };
    add_edge(0, 1, 1);
    add_edge(0, 2, 4);
    add_edge(1, 2, 2);
    add_edge(1, 3, 5);
    add_edge(2, 3, 1);

    auto res = ucs(g, 0, 3);
    for (size_t i = 0; i < res.first.size(); ++i)
    {
        if (i)
            cout << " ";
        cout << names[res.first[i]];
    }
    cout << " \n"
         << res.second << "\n";
}
