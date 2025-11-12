#include <bits/stdc++.h>
using namespace std;

vector<int> dls(const vector<vector<int>> &g, int s, int t, int lim)
{
    int n = (int)g.size();
    vector<pair<int, int>> st;
    st.push_back({s, 0});
    vector<int> par(n, -1);
    set<pair<int, int>> vis;
    vis.insert({s, 0});
    while (!st.empty())
    {
        auto [u, d] = st.back();
        st.pop_back();
        if (u == t)
        {
            vector<int> path;
            for (int x = u; x != -1; x = par[x])
                path.push_back(x);
            reverse(path.begin(), path.end());
            return path;
        }
        if (d < lim)
        {
            for (int v = n - 1; v >= 0; --v)
            {
                if (g[u][v] != -1 && !vis.count({v, d + 1}))
                {
                    vis.insert({v, d + 1});
                    par[v] = u;
                    st.push_back({v, d + 1});
                }
            }
        }
    }
    return {};
}

vector<int> iddfs(const vector<vector<int>> &g, int s, int t, int md)
{
    for (int l = 0; l <= md; ++l)
    {
        auto p = dls(g, s, t, l);
        if (!p.empty())
            return p;
    }
    return {};
}

int main()
{
    vector<string> names = {"A", "B", "C", "D", "E"};
    int n = (int)names.size();
    vector<vector<int>> g(n, vector<int>(n, -1));
    auto add_edge = [&](int u, int v)
    { g[u][v] = 1; };
    add_edge(0, 1);
    add_edge(0, 2);
    add_edge(1, 3);
    add_edge(2, 4);

    auto p = iddfs(g, 0, 4, 3);
    for (size_t i = 0; i < p.size(); ++i)
    {
        if (i)
            cout << " ";
        cout << names[p[i]];
    }
    cout << "\n";
}
