#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <string>

using namespace std;
struct unionfind {
    int n, c;
    vector<int> par, rank;
    unionfind(int n) : n(n), c(n), par(n, 0), rank(n, 0) {
        for (int i = 0; i < n; ++i) par[i] = i;
    }

    int find(int i) { return (par[i] == i ? i : (par[i] = find(par[i]))); }
    bool same(int i, int j) { return find(i) == find(j); }
    void Union(int i, int j) {
        if ((i = find(i)) == (j = find(j))) return;
        c--;
        if (rank[i] > rank[j]) swap(i, j);
        par[i] = j;
        if (rank[i] == rank[j]) rank[j]++;
    }
    int add() {
        c++;
        par.push_back(n);
        rank.push_back(0);
        n++;
        return n - 1;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    unionfind uf(200000);

    int V = 1;
    unordered_map<string, int> vertex;
    vector<bool> active(1, false);
    vector<int> suff[3];
    vector<pair<int, int> > NOT;
    suff[0].push_back(-1); suff[1].push_back(-1); suff[2].push_back(-1);
    string str[2], is, temp;
    for (int ai = 0; ai < N; ++ai) {
        cin >> str[0] >> is >> str[1];
        int str_id[2];
        for (int x = 0; x < 2; ++x) {
            string &lhs = str[x];
            auto it = vertex.find(lhs);
            if (it == vertex.end()) {
                vertex.insert({lhs, V});
                active.push_back(true);
                str_id[x] = V;
                for (int i = 0; i < 3; ++i)
                    suff[i].push_back(-1);
                uf.add();
                V++;
            } else {
                str_id[x] = it->second;
                active[str_id[x]] = true;
            }
            for (int L = 3; L > 0; --L) {
                if (lhs.length() > L) {
                    temp = lhs.substr(lhs.length() - L);
                    int ID = -1;
                    auto it2 = vertex.find(temp);
                    if (it2 == vertex.end()) {
                        ID = V;
                        vertex.insert({temp, V});
                        active.push_back(L == 3);
                        for (int i = 0; i < 3; ++i)
                            suff[i].push_back(-1);
                        uf.add();
                        V++;
                    } else ID = it2->second;
                    suff[L - 1][str_id[x]] = ID;
                }
            }
        }
        if (is == "is") uf.Union(str_id[0], str_id[1]);
        else NOT.push_back({str_id[0], str_id[1]});
    }

    // Resolve suffixes
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < 3; ++j)
            if (suff[j][i] == -1) continue;
            else if (!active[suff[j][i]]) continue;
            else uf.Union(suff[j][i], i);
    }

    bool yes = true;
    for (int i = 0; i < NOT.size() && yes; ++i) {
        yes = yes && !uf.same(NOT[i].first, NOT[i].second);
    }

    cout << (yes ? "yes" : "wait what?") << endl;

    return 0;
}