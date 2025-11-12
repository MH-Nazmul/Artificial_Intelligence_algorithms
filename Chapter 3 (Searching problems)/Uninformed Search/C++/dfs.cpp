#include <bits/stdc++.h>
using namespace std;

// DFS using adjacency matrix (2D vector). -1 means no edge, 1 means edge.
vector<int> dfs(const vector<vector<int>> &g, int s, int t)
{
    int n = (int)g.size();
    vector<int> st;
    st.push_back(s);
    vector<char> vis(n, 0);
    vis[s] = 1;
    vector<int> par(n, -1);
    while (!st.empty())
    {
        int u = st.back();
        st.pop_back();
        if (u == t)
        {
            vector<int> path;
            for (int x = u; x != -1; x = par[x])
                path.push_back(x);
            reverse(path.begin(), path.end());
            return path;
        }
        for (int v = (int)n - 1; v >= 0; --v)
        {
            if (g[u][v] != -1 && !vis[v])
            {
                vis[v] = 1;
                par[v] = u;
                st.push_back(v);
            }
        }
    }
    return {};
}

int main()
{
    vector<string> names = {"A", "B", "C", "D", "E", "F"};
    int n = (int)names.size();
    vector<vector<int>> g(n, vector<int>(n, -1));
    auto add_edge = [&](int u, int v)
    { g[u][v] = 1; };
    add_edge(0, 1);
    add_edge(0, 2);
    add_edge(1, 3);
    add_edge(1, 4);
    add_edge(2, 5);
    add_edge(4, 5);

    auto path = dfs(g, 0, 5);
    for (size_t i = 0; i < path.size(); ++i)
    {
        if (i)
            cout << " ";
        cout << names[path[i]];
    }
    cout << "\n";
}
