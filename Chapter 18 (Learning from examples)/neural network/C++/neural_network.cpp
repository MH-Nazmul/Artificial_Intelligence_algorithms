#include <bits/stdc++.h>
using namespace std;
double sigmoid(double x) { return 1.0 / (1.0 + exp(-x)); }
double dsigmoid(double y) { return y * (1.0 - y); }
struct MLP
{
    int ni, nh, no;
    vector<vector<double>> w1, w2;
    vector<double> b1, b2;
    MLP(int ni_, int nh_, int no_) : ni(ni_), nh(nh_), no(no_)
    {
        mt19937 rng(123);
        uniform_real_distribution<double> ur(-1.0, 1.0);
        w1.assign(nh, vector<double>(ni));
        for (int j = 0; j < nh; j++)
            for (int i = 0; i < ni; i++)
                w1[j][i] = ur(rng);
        b1.assign(nh, 0.0);
        w2.assign(no, vector<double>(nh));
        for (int k = 0; k < no; k++)
            for (int j = 0; j < nh; j++)
                w2[k][j] = ur(rng);
        b2.assign(no, 0.0);
    }
    pair<vector<double>, vector<double>> forward(const vector<double> &x)
    {
        vector<double> h(nh), o(no);
        for (int j = 0; j < nh; j++)
        {
            double s = b1[j];
            for (int i = 0; i < ni; i++)
                s += w1[j][i] * x[i];
            h[j] = sigmoid(s);
        }
        for (int k = 0; k < no; k++)
        {
            double s = b2[k];
            for (int j = 0; j < nh; j++)
                s += w2[k][j] * h[j];
            o[k] = sigmoid(s);
        }
        return {h, o};
    }
    void train(const vector<vector<double>> &X, const vector<vector<double>> &Y, double lr, int epochs)
    {
        for (int e = 0; e < epochs; e++)
        {
            for (size_t n = 0; n < X.size(); n++)
            {
                auto fo = forward(X[n]);
                auto h = fo.first;
                auto o = fo.second;
                vector<double> d2(no);
                for (int k = 0; k < no; k++)
                    d2[k] = (o[k] - Y[n][k]) * dsigmoid(o[k]);
                vector<double> d1(nh);
                for (int j = 0; j < nh; j++)
                {
                    double s = 0;
                    for (int k = 0; k < no; k++)
                        s += d2[k] * w2[k][j];
                    d1[j] = s * dsigmoid(h[j]);
                }
                for (int k = 0; k < no; k++)
                {
                    for (int j = 0; j < nh; j++)
                        w2[k][j] -= lr * d2[k] * h[j];
                    b2[k] -= lr * d2[k];
                }
                for (int j = 0; j < nh; j++)
                {
                    for (int i = 0; i < ni; i++)
                        w1[j][i] -= lr * d1[j] * X[n][i];
                    b1[j] -= lr * d1[j];
                }
            }
        }
    }
    vector<double> predict(const vector<double> &x) { return forward(x).second; }
};
int main()
{
    vector<vector<double>> X{{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    vector<vector<double>> Y{{0}, {1}, {1}, {0}};
    MLP net(2, 3, 1);
    net.train(X, Y, 0.5, 5000);
    for (auto &x : X)
    {
        auto o = net.predict(x);
        cout << x[0] << "," << x[1] << ":" << o[0] << "\n";
    }
}
