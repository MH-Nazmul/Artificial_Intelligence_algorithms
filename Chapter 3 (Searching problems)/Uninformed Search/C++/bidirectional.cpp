#include <bits/stdc++.h>
using namespace std;

// Bidirectional BFS on adjacency matrix (2D vector). -1 means no edge.
vector<int> bidir(const vector<vector<int>> &g, int s, int t)
{
    if (s == t)
        return {s};
    int n = (int)g.size();
    queue<int> q1, q2;
    q1.push(s);
    q2.push(t);
    vector<int> p1(n, -1), p2(n, -1);
    vector<char> v1(n, 0), v2(n, 0);
    v1[s] = 1;
    v2[t] = 1;
    int meet = -1;
    // Continue while either frontier has nodes (supports directed graphs where one side may stall)
    while (!q1.empty() || !q2.empty())
    {
        // Expand from source side if available
        int qs = (int)q1.size();
        while (qs-- && !q1.empty())
        {
            int u = q1.front();
            q1.pop();
            for (int x = 0; x < n; ++x)
            {
                if (g[u][x] != -1 && !v1[x])
                {
                    v1[x] = 1;
                    p1[x] = u;
                    q1.push(x);
                    if (v2[x])
                    {
                        meet = x;
                        while (!q2.empty())
                            q2.pop();
                        break;
                    }
                }
            }
            if (meet != -1)
                break;
        }
        if (meet != -1)
            break;
        // Expand from target side if available
        int qt = (int)q2.size();
        while (qt-- && !q2.empty())
        {
            int v = q2.front();
            q2.pop();
            for (int y = 0; y < n; ++y)
            {
                if (g[v][y] != -1 && !v2[y])
                {
                    v2[y] = 1;
                    p2[y] = v;
                    q2.push(y);
                    if (v1[y])
                    {
                        meet = y;
                        while (!q1.empty())
                            q1.pop();
                        break;
                    }
                }
            }
            if (meet != -1)
                break;
        }
        if (meet != -1)
            break;
    }
    if (meet == -1)
        return {};
    vector<int> left;
    for (int x = meet; x != -1; x = p1[x])
        left.push_back(x);
    reverse(left.begin(), left.end());
    vector<int> right;
    for (int y = p2[meet]; y != -1; y = p2[y])
        right.push_back(y);
    left.insert(left.end(), right.begin(), right.end());
    return left;
}

int main()
{
    vector<string> names = {"A", "B", "C", "D", "E"};
    int n = (int)names.size();
    vector<vector<int>> g(n, vector<int>(n, -1));
    auto add_edge = [&](int u, int v)
    { g[u][v] = 1; };
    add_edge(0, 1);
    add_edge(1, 2);
    add_edge(2, 3);
    add_edge(3, 4);

    auto p = bidir(g, 0, 4);
    for (size_t i = 0; i < p.size(); ++i)
    {
        if (i)
            cout << " ";
        cout << names[p[i]];
    }
    cout << "\n";
}
