#include <bits/stdc++.h>
using namespace std;
double entropy(const vector<string> &y)
{
    unordered_map<string, int> c;
    for (auto &v : y)
        c[v]++;
    double n = y.size();
    double e = 0;
    for (auto &kv : c)
    {
        double p = kv.second / n;
        e -= p * log2(p);
    }
    return e;
}
string majority(const vector<string> &y)
{
    unordered_map<string, int> c;
    for (auto &v : y)
        c[v]++;
    return max_element(c.begin(), c.end(), [](auto &a, auto &b)
                       { return a.second < b.second; })
        ->first;
}
double info_gain(const vector<vector<int>> &X, const vector<string> &y, int feat)
{
    double n = y.size();
    double e = entropy(y);
    unordered_map<int, vector<int>> groups;
    for (int i = 0; i < (int)X.size(); i++)
        groups[X[i][feat]].push_back(i);
    double s = 0;
    for (auto &kv : groups)
    {
        vector<string> py;
        for (int idx : kv.second)
            py.push_back(y[idx]);
        s += kv.second.size() / n * entropy(py);
    }
    return e - s;
}
struct Node
{
    bool leaf;
    string label;
    int feat;
    unordered_map<int, Node *> child;
};
Node *build(vector<vector<int>> X, vector<string> y, vector<int> feats)
{
    if (set<string>(y.begin(), y.end()).size() == 1)
    {
        Node *t = new Node{true, y[0], -1, {}};
        return t;
    }
    if (feats.empty())
    {
        Node *t = new Node{true, majority(y), -1, {}};
        return t;
    }
    vector<pair<double, int>> gains;
    for (int f : feats)
        gains.push_back({info_gain(X, y, f), f});
    sort(gains.begin(), gains.end(), greater<>());
    int best = gains[0].second;
    unordered_map<int, vector<int>> groups;
    for (int i = 0; i < (int)X.size(); i++)
        groups[X[i][best]].push_back(i);
    Node *t = new Node{false, "", best, {}};
    for (auto &kv : groups)
    {
        int v = kv.first;
        auto &ids = kv.second;
        vector<vector<int>> Xv;
        vector<string> yv;
        for (int idx : ids)
        {
            vector<int> row = X[idx];
            row.erase(row.begin() + best);
            Xv.push_back(row);
            yv.push_back(y[idx]);
        }
        vector<int> nf;
        for (int f : feats)
            if (f != best)
                nf.push_back(f > best ? f - 1 : f);
        t->child[v] = build(Xv, yv, nf);
    }
    return t;
}
string predict(Node *t, vector<int> x)
{
    while (!t->leaf)
    {
        int f = t->feat;
        int v = x[f];
        if (!t->child.count(v))
            return "";
        x.erase(x.begin() + f);
        t = t->child[v];
    }
    return t->label;
}
int main()
{
    vector<vector<string>> X{{"sunny", "hot", "high", "weak"}, {"sunny", "hot", "high", "strong"}, {"overcast", "hot", "high", "weak"}, {"rain", "mild", "high", "weak"}, {"rain", "cool", "normal", "weak"}, {"rain", "cool", "normal", "strong"}, {"overcast", "cool", "normal", "strong"}, {"sunny", "mild", "high", "weak"}, {"sunny", "cool", "normal", "weak"}, {"rain", "mild", "normal", "weak"}, {"sunny", "mild", "normal", "strong"}, {"overcast", "mild", "high", "strong"}, {"overcast", "hot", "normal", "weak"}, {"rain", "mild", "high", "strong"}};
    vector<string> y{"no", "no", "yes", "yes", "yes", "no", "yes", "no", "yes", "yes", "yes", "yes", "yes", "no"};
    unordered_map<string, int> enc;
    int idc = 0;
    vector<vector<int>> Xenc;
    for (auto &row : X)
    {
        vector<int> r;
        for (auto &v : row)
        {
            if (!enc.count(v))
                enc[v] = idc++;
            r.push_back(enc[v]);
        }
        Xenc.push_back(r);
    }
    vector<int> feats;
    for (int i = 0; i < (int)Xenc[0].size(); i++)
        feats.push_back(i);
    Node *tree = build(Xenc, y, feats);
    vector<string> x{"sunny", "cool", "high", "strong"};
    vector<int> xenc;
    for (auto &v : x)
        xenc.push_back(enc[v]);
    cout << predict(tree, xenc) << "\n";
}
