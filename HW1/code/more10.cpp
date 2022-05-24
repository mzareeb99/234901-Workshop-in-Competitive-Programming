#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<ull> vull;
typedef vector<bool> vb;
typedef vector<vi> v2i;
typedef priority_queue<int> max_iheap;
typedef priority_queue<ll> max_llheap;
typedef priority_queue<ull> max_ullheap;
typedef priority_queue<int, vi, greater<int>> min_iheap;
typedef priority_queue<int, vll, greater<ll>> min_llheap;
typedef priority_queue<int, vull, greater<ull>> min_ullheap;
typedef vector<pair<double,double>> vpd;
typedef pair<int,int> ii;
typedef pair<double,double> dd;
typedef pair<dd,double> ddd;
typedef pair<int,ii> iii;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef set<int> si;
typedef vector<si> vsi;
typedef vector< vector<int> > vvi; // unweighted graph
typedef vector< vector< pair<int,int> > > vvii; // weighted graph
using namespace std;


map<string, int> ver;
vb act(1, false);
vi suff[3];
vii _not;

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



bool checkIfIsRyh(unionfind& uf){
    bool ret = true;
    for (int i = 0; i < _not.size() && ret; ++i) {
        ret = ret && !uf.same(_not[i].first, _not[i].second);
    }
    return ret;
}

int aux(int N,unionfind& uf){
    int num=1;
    string str[2], is, temp;
    for (int k = 0; k < N; ++k) {
        cin >> str[0] >> is >> str[1];
        int str_id[2];
        for (int x = 0; x < 2; ++x) {
            string &lhs = str[x];
            if (ver.find(lhs) == ver.end()) {
                ver[lhs]= num;
                act.push_back(true);
                str_id[x] = num;
                for (auto & i : suff)
                    i.push_back(-1);
                uf.add();
                num++;
            } else {
                str_id[x] = ver[lhs];
                act[str_id[x]] = true;
            }
            for (int L = 3; L > 0; --L) {
                if (lhs.length() > L) {
                    temp = lhs.substr(lhs.length() - L);
                    int id;
                    if (ver.find(temp) == ver.end()) {
                        id = num;
                        ver[temp]= num;
                        act.push_back(L == 3);
                        for (auto & i : suff)
                            i.push_back(-1);
                        uf.add();
                        num++;
                    } else id = ver[temp];
                    suff[L - 1][str_id[x]] = id;
                }
            }
        }
        if (is == "is") uf.Union(str_id[0], str_id[1]);
        else _not.push_back({str_id[0], str_id[1]});
    }
    return num;
}



int main() {
    int N;
    cin >> N;
    unionfind uf(200000);
    suff[0]={-1}; suff[1]={-1}; suff[2]={-1};
    int V = aux(N,uf);
    for (int i = 0; i < V; ++i) {
        for (auto & j : suff)
             if (j[i] == -1||!act[j[i]]) continue;
            else uf.Union(j[i], i);
    }
    cout << (checkIfIsRyh(uf) ? "yes" : "wait what?") << endl;
    return 0;
}
