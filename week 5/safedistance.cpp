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
template<typename T>
T distance(pair<T,T>& a, pair<T,T>& b){
    return sqrt((a.first-b.first)*(a.first-b.first)+(a.second - b.second)*(a.second - b.second));
}
double distance(dd &a, dd&b){
    return distance<double>(a,b);
}


int X,Y,N;
vector<dd> people;

bool check(double mid){
    int top =N, bottom =N+1, left = N+2, right =N+3;
    UnionFind uf(N+4);

    for(int i = 0 ; i< N ; i++){
        if(Y - people[i].second <= mid) uf.Union(i,top);
        if(people[i].second <= mid) uf.Union(i,bottom);
        if(X - people[i].first <= mid) uf.Union(i,right);
        if(people[i].first <=mid) uf.Union(i,left);
    }

    for(int i = 0 ; i < N;i++){
        for(int j = i+1; j < N;j++){
            if(distance(people[i],people[j]) <= 2*mid) uf.Union(i,j);
        }
    }

    return uf.find(top)==uf.find(bottom) || uf.find(top)==uf.find(right)||
    uf.find(bottom)==uf.find(left) || uf.find(left)==uf.find(right);

}

int main(){
    cin >>X>>Y>>N;
    double xi,yi;
    int temp = N;
    while(temp--){
        cin>>xi>>yi;
        people.push_back({xi,yi});
    }
    dd a = {X,Y}, b ={0.0,0.0};
    double bottom = 0.0,  top = distance(a,b);
    double mid, ret = 0.0;
    while(fabs(top - bottom) > eps){
        mid = (bottom + top)/2.0;
        if(check(mid)) top = mid, ret = mid;
        else bottom = mid;
    }
    printf("%0.6f",ret);
    return 0;
}