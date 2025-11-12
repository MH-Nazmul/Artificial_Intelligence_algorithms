#include <bits/stdc++.h>
#include <bits/stdc++.h>
using namespace std;

// A* Search on adjacency matrix with non-negative weights and heuristic vector.
vector<int> astar(const vector<vector<int>> &g, const vector<int> &h, int s, int t)
{
    int n = (int)g.size();
    using T = tuple<int, int, int>; // f, g, node
    priority_queue<T, vector<T>, greater<T>> openq;
    openq.push({h[s], 0, s});
    vector<int> gval(n, INT_MAX), par(n, -1);
    gval[s] = 0;
    vector<char> closed(n, 0);
    while (!openq.empty())
    {
        auto [f, gv, u] = openq.top();
        openq.pop();
        if (closed[u])
            continue;
        if (u == t)
        {
            vector<int> path;
            for (int x = u; x != -1; x = par[x])
                path.push_back(x);
            reverse(path.begin(), path.end());
            return path;
        }
        closed[u] = 1;
        for (int v = 0; v < n; ++v)
        {
            int w = g[u][v];
            if (w != -1)
            {
                int ng = gval[u] + w;
                if (ng < gval[v])
                {
                    gval[v] = ng;
                    par[v] = u;
                    openq.push({ng + h[v], ng, v});
                }
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
    auto add_edge = [&](int u, int v, int w)
    { g[u][v] = w; };
    add_edge(0, 1, 1);
    add_edge(0, 2, 4);
    add_edge(1, 2, 2);
    add_edge(1, 3, 5);
    add_edge(2, 3, 1);
    vector<int> h = {7, 6, 2, 0};

    auto p = astar(g, h, 0, 3);
    for (size_t i = 0; i < p.size(); ++i)
    {
        if (i)
            cout << " ";
        cout << names[p[i]];
    }
    cout << "\n";
}
