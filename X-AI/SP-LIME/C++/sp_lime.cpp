#include <bits/stdc++.h>
using namespace std;
vector<int> sp_lime(const vector<vector<double>> &exps, int k)
{
    unordered_map<int, double> scores;
    for (auto &beta : exps)
    {
        for (int i = 0; i < (int)beta.size(); i++)
            scores[i] += fabs(beta[i]);
    }
    vector<pair<int, double>> v(scores.begin(), scores.end());
    sort(v.begin(), v.end(), [](auto &a, auto &b)
         { return a.second > b.second; });
    vector<int> res;
    for (int i = 0; i < k && i < (int)v.size(); i++)
        res.push_back(v[i].first);
    return res;
}
int main()
{
    vector<vector<double>> exps{{0.3, -0.1, 0.0}, {0.2, 0.4, 0.1}, {0.0, 0.5, 0.2}};
    auto r = sp_lime(exps, 2);
    for (size_t i = 0; i < r.size(); ++i)
    {
        if (i)
            cout << " ";
        cout << r[i];
    }
    cout << "\n";
}
