#include <bits/stdc++.h>
using namespace std;
struct GaussianNB
{
    vector<int> classes;
    unordered_map<int, double> prior;
    unordered_map<int, vector<double>> mu;
    unordered_map<int, vector<double>> s2;
    void fit(const vector<vector<double>> &X, const vector<int> &y)
    {
        int n = X.size();
        set<int> cs(y.begin(), y.end());
        classes.assign(cs.begin(), cs.end());
        unordered_map<int, vector<int>> idx;
        for (int i = 0; i < n; i++)
            idx[y[i]].push_back(i);
        int d = X[0].size();
        for (int c : classes)
        {
            auto &ids = idx[c];
            prior[c] = (double)ids.size() / n;
            vector<double> m(d, 0.0);
            vector<double> v(d, 0.0);
            for (int j = 0; j < d; j++)
            {
                for (int i : ids)
                    m[j] += X[i][j];
                m[j] /= ids.size();
            }
            for (int j = 0; j < d; j++)
            {
                double s = 0;
                for (int i : ids)
                {
                    double t = X[i][j] - m[j];
                    s += t * t;
                }
                v[j] = s / max(1, (int)ids.size() - 1);
            }
            mu[c] = m;
            s2[c] = v;
        }
    }
    double logpdf(const vector<double> &x, const vector<double> &m, const vector<double> &v)
    {
        double eps = 1e-9;
        double s = 0;
        int d = x.size();
        for (int j = 0; j < d; j++)
        {
            double vv = v[j] + eps;
            s += -0.5 * log(2 * M_PI * vv) - 0.5 * (x[j] - m[j]) * (x[j] - m[j]) / vv;
        }
        return s;
    }
    int predict(const vector<double> &x)
    {
        int best = classes[0];
        double bestv = -1e300;
        for (int c : classes)
        {
            double lp = log(prior[c]) + logpdf(x, mu[c], s2[c]);
            if (lp > bestv)
            {
                bestv = lp;
                best = c;
            }
        }
        return best;
    }
};
int main()
{
    vector<vector<double>> X{{1.0, 2.0}, {1.2, 1.9}, {3.0, 3.5}, {2.9, 3.6}};
    vector<int> y{0, 0, 1, 1};
    GaussianNB nb;
    nb.fit(X, y);
    cout << nb.predict({1.1, 2.1}) << " " << nb.predict({3.1, 3.4}) << "\n";
}
