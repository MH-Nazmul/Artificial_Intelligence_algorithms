#include <bits/stdc++.h>
using namespace std;

// Greedy Best-First Search using adjacency matrix and heuristic vector.
vector<int> gbfs(const vector<vector<int>> &g, const vector<int> &h, int s, int t)
{
    int n = (int)g.size();
    using P = pair<int, int>; // (h(node), node)
    priority_queue<P, vector<P>, greater<P>> pq;
    pq.push({h[s], s});
    vector<char> vis(n, 0);
    vector<int> par(n, -1);
    while (!pq.empty())
    {
        auto [hv, u] = pq.top();
        pq.pop();
        if (vis[u])
            continue;
        if (u == t)
        {
            vector<int> path;
            for (int x = u; x != -1; x = par[x])
                path.push_back(x);
            reverse(path.begin(), path.end());
            return path;
        }
        vis[u] = 1;
        for (int v = 0; v < n; ++v)
        {
            if (g[u][v] != -1 && !vis[v])
            {
                par[v] = u;
                pq.push({h[v], v});
            }
        }
    }
    return {};
}

int main()
{
    vector<string> names = {"A", "B", "C", "D"};
    int n = (int)names.size();
    vector<vector<int>> g(n, vector<int>(n, -1));
    auto add_edge = [&](int u, int v)
    { g[u][v] = 1; };
    add_edge(0, 1);
    add_edge(0, 2);
    add_edge(1, 3);
    add_edge(2, 3);
    vector<int> h = {3, 2, 1, 0};

    auto p = gbfs(g, h, 0, 3);
    for (size_t i = 0; i < p.size(); ++i)
    {
        if (i)
            cout << " ";
        cout << names[p[i]];
    }
    cout << "\n";
}
