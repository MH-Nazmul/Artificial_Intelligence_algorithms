#include <bits/stdc++.h>
using namespace std;
vector<double> linear_regression(const vector<vector<double>> &X, const vector<double> &y, const vector<double> &w)
{
    int d = X[0].size();
    vector<vector<double>> A(d, vector<double>(d, 0));
    vector<double> b(d, 0);
    for (size_t i = 0; i < X.size(); i++)
    {
        double wi = w[i];
        for (int j = 0; j < d; j++)
        {
            b[j] += wi * y[i] * X[i][j];
            for (int k = 0; k < d; k++)
                A[j][k] += wi * X[i][j] * X[i][k];
        }
    }
    for (int j = 0; j < d; j++)
        A[j].push_back(b[j]);
    for (int i = 0; i < d; i++)
    {
        int piv = i;
        for (int r = i + 1; r < d; r++)
            if (fabs(A[r][i]) > fabs(A[piv][i]))
                piv = r;
        swap(A[i], A[piv]);
        if (fabs(A[i][i]) < 1e-12)
            continue;
        double fac = A[i][i];
        for (int c = i; c <= d; c++)
            A[i][c] /= fac;
        for (int r = 0; r < d; r++)
            if (r != i)
            {
                double f = A[r][i];
                for (int c = i; c <= d; c++)
                    A[r][c] -= f * A[i][c];
            }
    }
    vector<double> beta(d);
    for (int j = 0; j < d; j++)
        beta[j] = A[j][d];
    return beta;
}
vector<double> explain(function<double(vector<double>)> model, const vector<double> &x, int num_samples = 500, double sigma = 0.1)
{
    int d = x.size();
    vector<vector<double>> X;
    vector<double> y, w;
    mt19937 rng(123);
    normal_distribution<double> nd(0, sigma);
    for (int s = 0; s < num_samples; s++)
    {
        vector<double> z(d);
        for (int i = 0; i < d; i++)
            z[i] = x[i] + nd(rng);
        double p = model(z);
        vector<double> feat(d);
        for (int i = 0; i < d; i++)
            feat[i] = z[i] - x[i];
        X.push_back(feat);
        y.push_back(p);
        double dist = 0;
        for (int i = 0; i < d; i++)
        {
            double diff = z[i] - x[i];
            dist += diff * diff;
        }
        dist = sqrt(dist);
        w.push_back(exp(-dist * dist / (2 * sigma * sigma)));
    }
    return linear_regression(X, y, w);
}
int main()
{
    auto model = [](vector<double> z)
    { return z[0] + 2 * z[1] > 0 ? 1.0 : 0.0; };
    vector<double> x{0.1, -0.2};
    auto beta = explain(model, x);
    for (size_t i = 0; i < beta.size(); ++i)
    {
        if (i)
            cout << " ";
        cout << beta[i];
    }
    cout << "\n";
}
