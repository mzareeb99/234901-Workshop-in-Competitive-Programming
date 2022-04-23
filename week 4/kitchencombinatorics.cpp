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
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<ull> vull;
typedef vector<bool> vb;
typedef vector<vi> v2i;
typedef pair<int, int> pii;
typedef priority_queue<int> max_iheap;
typedef priority_queue<ll> max_llheap;
typedef priority_queue<ull> max_ullheap;
typedef priority_queue<int, vi, greater<int>> min_iheap;
typedef priority_queue<int, vll, greater<ll>> min_llheap;
typedef priority_queue<int, vull, greater<ull>> min_ullheap;
#define print(x) cout<<x<<endl
int s, m, d;
vb vis;
vi R, A, B, C;
v2i G, ING;
ull INF = 1e18;
ull solve(int k) {
    ull res = 0;
    if (k == 3) {
        vi count(R.size(), 0);
        for (int i = 0; i < vis.size(); ++i) {
            if (vis[i]) for (int r : ING[i]) ++count[r];
        }
        res = 1;
        for (int i = 0; i < count.size(); ++i) {
            if (!count[i]) continue;
            if (R[i] == -1) {
                return -1;
            }
            __int128 t = res;
            t *= R[i];
            if (t > INF) {
                return -1;
            }
            res = t;
        }
        return res;
    }
    for (int i = A[k]; i < B[k]; ++i) {
        bool temp = false;

        for (int c : G[i]) if (vis[c]){temp =true;
                break;}
        if(temp)
            continue;
        vis[i] = true;
        ull r = solve(k + 1);
        vis[i] = false;
        if(r==-1){
            return -1;
        }
        ull t = res;
        t+=r;
        if(t>INF){
            return -1;
        }
        res = t;
    }
    return res;
}
int main() {
    int r, n;
    cin >> r >> s >> m >> d >> n;
    R.resize(r), G.resize(s + m + d), ING.resize(G.size());
    vis.assign(G.size(), false), C.assign(r, 0);
    A = {0, s, s + m};
    B = {s, s + m, s + m + d};
    for (int i = 0; i < r; ++i) cin >> R[i];
    for (int i = 0; i < ING.size(); ++i) {
        int k;
        cin >> k;
        ING[i] = vi(k);
        for (auto &e : ING[i]) cin >> e, --e;
    }
    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        G[a].push_back(b), G[b].push_back(a);
    }
    ull res = solve(0);
    if (res == -1) printf("too many\n");
    else printf("%lld\n", res);
    return 0;
}