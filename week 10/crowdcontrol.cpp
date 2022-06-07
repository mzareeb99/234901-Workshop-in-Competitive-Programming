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
#include <iomanip>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<ull> vull;
typedef vector<vll> vvll;
typedef vector<vull> vvull;
typedef pair<int, int> pii;
typedef pii ii;
typedef pair<int, ii> iii;
typedef vector<pii> vii;
typedef priority_queue<int> max_iheap;
typedef priority_queue<ll> max_llheap;
typedef priority_queue<ull> max_ullheap;
typedef priority_queue<int, vi, greater<int>> min_iheap;
typedef priority_queue<int, vll, greater<ll>> min_llheap;
typedef priority_queue<int, vull, greater<ull>> min_ullheap;
typedef vector< vector<int> > vvi; // unweighted graph
typedef vector< vector< pair<int,int> > > vvii; // weighted graph
#define fastIO ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)


typedef pair<int,int> ii;
typedef pair<int,ii> iii;
typedef pair<int,iii> iiii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef set<int> si;
typedef vector<si> vsi;

const int INF = 1e9;

struct unionfind {
    vector<int> rank;
    vector<int> parent;

    unionfind (int size) {
        rank=vector<int>(size,0);
        parent=vector<int>(size);
        for(int i=0;i<size;i++) parent[i]=i;
    }

    int find(int x) {
        int tmp=x;
        while(x!=parent[x]) x=parent[x];
        while(tmp!=x) {
            int remember=parent[tmp];
            parent[tmp]=x;
            tmp=remember;
        }
        return x;
    }

    void unite(int p, int q) {
        p = find(p);
        q = find(q);
        if(q==p) return;
        if(rank[p] < rank[q]) parent[p] = q;
        else parent[q] = p;
        if(rank[p] == rank[q]) rank[p]++;
    }
};


// input: edges v1->v2 of the form (weight,(v1,v2)),
//        number of nodes (n), all nodes are between 0 and n-1.
// output: weight of a minimum spanning tree.
// time: O(ElogV).
int Kruskal(vector<iiii>& edges, int n, vector<iiii>& mst) {
    sort(edges.begin(), edges.end());
    int mst_cost = 0;
    unionfind components(n);
    for (iiii& e : edges) {
        if (components.find(e.second.second.first) != components.find(e.second.second.second)) {
            mst_cost += e.first;
            components.unite(e.second.second.first, e.second.second.second);
            mst.push_back(e);

//            e.second.second.first = n+1;
//            e.second.second.second = n+1;
        }
    }
    return mst_cost;
}


void getOnlyPath(const vector<iiii>& mst, int n, si& nodes_in_path, si& except){
    vvii g(n);
    for (const auto& p : mst){
        g[p.second.second.first].emplace_back(p.second.second.second, p.second.first);
        g[p.second.second.second].emplace_back(p.second.second.first, p.second.first);
    }
    queue<int> q; q.push(0);
    vector<bool> visible (g.size(),false);
    vii p(n, {0, 0});
    visible[0]=true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (u == n-1){
            break;
        }
        for (auto vp: g[u]) {
            int v = vp.first;
            if (!visible[v]) {
                visible[v] = true;
                q.push(v);
                p[v] = {u, vp.second};
            }
        }
    }
    for (int i=n-1; i!=0; i=p[i].first){
        int num=p[i].second;
        nodes_in_path.insert(i);
        except.insert(num);
    }
    nodes_in_path.insert(0);
}

int main(){
    fastIO;

    int n, m;
    cin >> n >> m;

    vector<iiii> edges;
    for (int i=0; i<m; ++i){
        int s, d, w;
        cin >> s >> d >> w;
        edges.push_back({-w, {i, {s, d}}});
    }

    vector<iiii> mst;
    Kruskal(edges, n, mst);

    si avoid;
    si except;
    getOnlyPath(mst, n, avoid, except);

    si sol;

    for (const auto& e : edges){
        if ((avoid.find(e.second.second.first) != avoid.end()) ||
            (avoid.find(e.second.second.second) != avoid.end())){
            if (except.find(e.second.first) == except.end()){
                sol.insert(e.second.first);
            }
        }
    }

    if (sol.empty()){
        cout << "none" << endl;
    } else{
        int counter = 0;
        for (auto i : sol){
            ++counter;
            cout << i;
            if (counter != sol.size()){
                cout << " ";
            } else{
                cout << endl;
            }
        }
    }

    return 0;
}
