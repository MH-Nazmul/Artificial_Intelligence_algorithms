#include <bits/stdc++.h>
using namespace std;
struct NGram
{
    int n;
    map<pair<vector<string>, string>, int> counts;
    map<vector<string>, int> ctx_counts;
    NGram(int n_) : n(n_) {}
    void train(const vector<string> &tokens)
    {
        vector<string> pad(n - 1, "<s>");
        vector<string> seq = pad;
        seq.insert(seq.end(), tokens.begin(), tokens.end());
        seq.push_back("</s>");
        for (int i = n - 1; i < (int)seq.size(); i++)
        {
            vector<string> ctx;
            for (int k = i - n + 1; k < i; k++)
                ctx.push_back(seq[k]);
            string tok = seq[i];
            counts[{ctx, tok}]++;
            ctx_counts[ctx]++;
        }
    }
    double prob(const vector<string> &ctx, const string &tok)
    {
        vector<string> c = ctx;
        set<string> vocab;
        for (auto &kv : counts)
            vocab.insert(kv.first.second);
        int num = counts[{c, tok}] + 1;
        int den = ctx_counts[c] + (int)vocab.size();
        return (double)num / den;
    }
    vector<string> generate(int max_len = 20)
    {
        vector<string> ctx(n - 1, "<s>");
        vector<string> out;
        for (int t = 0; t < max_len; t++)
        {
            set<string> vocab;
            vector<string> c = ctx;
            for (auto &kv : counts)
                if (kv.first.first == c)
                    vocab.insert(kv.first.second);
            if (vocab.empty())
                break;
            vector<string> v(vocab.begin(), vocab.end());
            vector<double> w;
            double s = 0;
            for (auto &tok : v)
            {
                double p = prob(ctx, tok);
                w.push_back(p);
                s += p;
            }
            double r = ((double)rand() / RAND_MAX) * s;
            double acc = 0;
            string pick = v.back();
            for (size_t i = 0; i < v.size(); i++)
            {
                acc += w[i];
                if (acc >= r)
                {
                    pick = v[i];
                    break;
                }
            }
            if (pick == "</s>")
                break;
            out.push_back(pick);
            ctx.erase(ctx.begin());
            ctx.push_back(pick);
        }
        return out;
    }
};
int main()
{
    vector<string> text;
    string s = "the cat sat on the mat the cat saw a rat";
    string tmp;
    stringstream ss(s);
    while (ss >> tmp)
        text.push_back(tmp);
    NGram lm(2);
    lm.train(text);
    auto out = lm.generate();
    for (size_t i = 0; i < out.size(); ++i)
    {
        if (i)
            cout << " ";
        cout << out[i];
    }
    cout << "\n";
}
