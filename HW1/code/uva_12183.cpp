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

#define print(x) cout<<x<<endl
#define eps 1e-6
#define INF 1e9
#define UNVISITED 0
#define VISITED 1
#define  MAX_SIZE 2000001




void dfs(const vvi& g, int s) {
    stack<int> q; q.push(s);
    vector<bool> visible (g.size(),false);
    visible[s]=true;
    while (!q.empty()) {
        int u = q.top(); q.pop(); printf("%d\n", u);
        for (int v : g[u]) if (!visible[v]) {
                visible[v] = true;
                q.push(v);
            }
    }
}
void bfs(const vvi& g, int s) {
    queue<int> q; q.push(s); vector<bool> visible (g.size(),false); visible[s]=true;
    while (!q.empty()) {
        int u = q.front() ; q.pop(); printf("%d\n", u);
        for (int v : g[u]) if (!visible[v]) {
                visible[v] = true;
                q.push(v);
            }
    }
}
void KosarajuDFS(const vvi& g, int u, int color, vi& S, vi& colorMap) {
    colorMap[u] = color;
    for (auto& v : g[u]) if (colorMap[v] == 0)
            KosarajuDFS(g, v, color,S,colorMap); S.push_back(u);
}
bool topologicalSort(const vvi& g, vi& order) {
// compute indegree of all nodes
    vi indegree (g.size(), 0);
    for (int v=0; v<g.size(); v++) for (int u : g[v]) indegree[u]++; // order sources first
    order = vector<int>();
    for (int v=0; v<g.size(); v++) if (indegree[v] == 0) order.push_back(v);
// go over the ordered nodes and remove outgoing edges, add new sources to the ordering for (int i=0; i<order.size(); i++) for (int u : g[order[i]]) {
    for (int i=0; i<order.size(); i++) for (int u : g[order[i]]) {
            indegree[u]--;
            if (indegree[u]==0) order.push_back(u);}
    return order.size()==g.size();
}
int findSCC(const vvi& g, vi& components) {
// first pass: record the `post-order' of original graph. vi order, seen;
    vi order, seen;
    seen.assign(g.size(), 0);
    for (int i = 0; i < g.size(); ++i) if (seen[i] == 0)
            KosarajuDFS(g, i, 1, order, seen);
// second pass: explore the SCCs based on first pass result.
    vvi reverse_g(g.size(),vi()); for (int u=0; u<g.size(); u++) for (int v : g[u]) reverse_g[v].push_back(u); int numSCC = 0; components.assign(g.size(), 0);
    vi dummy;
    for (int i = (int)g.size()-1; i >= 0; --i) if (components[order[i]] == 0)
            KosarajuDFS(reverse_g, order[i], numSCC++, dummy, components); return numSCC; }
void Dijkstra(const vvii& g, int s, vi& d){
    d = vi(g.size(),INF);
    d[s] = 0;
    priority_queue<ii, vii, greater<ii>> q;
    q.push({0, s});
    while (!q.empty()) {
        ii front = q.top(); q.pop();
        int dist = front.first, u = front.second;
        if (dist > d[u]) continue;
        for (ii next : g[u]) {
            int v = next.first, w = next.second;
            if (d[u]+w < d[v]) {
                d[v] = d[u]+w;
                q.push({d[v], v});
            }
        }
    }
}
struct UnionFind{
    vector<int> rank;
    vector<int> parent;
    vi sizes;

    explicit UnionFind(int size){
        rank=vector<int>(size,0);
        parent=vector<int>(size);
        for(int i=0;i<size;i++)
            parent[i]=i;
        sizes = vi(size, 1);
    }

    int find(int x){
        int tmp=x;
        while(x!=parent[x]) x=parent[x];
        while(tmp!=x){
            int remember=parent[tmp];
            parent[tmp]=x;
            tmp=remember;
        }
        return x;
    }

    void Union(int p, int q){
        p = find(p);
        q = find(q);
        if(q==p){
            return;
        }
        if(rank[p] < rank[q]){
            parent[p] = q;
            sizes[q] += sizes[p];
        }
        else{
            parent[p] = q;
            sizes[q] += sizes[p];
        }

        if(rank[p] == rank[q])
            rank[p]++;
    }
};


ull mod;
vector<ull> multiply(vector<ull> &A, vector<ull> &B) {
    int n = A.size();
    vector<ull> C(n);
    for (int i = 0; i < n; i++) {
        ull tmp = 0;
        for (int j = 0; j < n; ++j) {
            if (j <= i) {
                tmp += (A[j] * B[i - j]) % mod;
            } else {
                tmp += (A[j] * B[n + (i - j)]) % mod;
            }
            tmp = tmp % mod;
        }
        C[i] = tmp % mod;
    }

    return C;
}


int main() {
    ull T;
    while (cin >> T) {
        for (ull j = 0; j < T; ++j) {
            ull N, S, L, R, X;
            cin >> N >> S >> L >> R >> X;
            vector<ull> nums(N);
            for (int i = 0; i < N; ++i) {
                cin >> nums[i];
            }
            vector<ull> A(N, 0);
            A[0] = 1;
            A[1] = R;
            A[N - 1] = L;
            mod = (ull)pow(10, X);
            ull k=S;
            vector<ull> ret(A.size(), 0);
            ret[0] = 1;
            vector<ull> B(A.size());
            B[0] = A[0];
            for (int i = 1; i < A.size(); ++i) {
                B[i] = A[A.size() - i];
            }
            while (k) {
                if (k % 2==1)
                    ret = multiply(ret, B);
                B = multiply(B, B);
                k /= 2;
            }
            ull n = 0;
            for (auto &num : multiply(nums, ret)) {
                cout << (num % mod);
                if (n != N - 1) {
                    cout << " ";
                } else {
                    cout << endl;
                }
                n++;
            }
        }
    }
    return 0;
}
