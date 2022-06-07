#include <iostream>
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
#include <vector>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> ii;
typedef pair<int,ii> iii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef set<int> si;
typedef vector<si> vsi;

const int INF = 1e9;
vector<iii> edges , ans;
map<pair<int,int>,int> mymap;

int augment(vvi& res, int s, int t, const vi& p, int minEdge) {
    // traverse the path from s to t according to p.
    // change the residuals on this path according to the min edge weight along this path.
    // return the amount of flow that was added.
    if (t == s) {
        return minEdge;
    } else if (p[t] != -1) {
        int f = augment(res, s, p[t], p, min(minEdge, res[p[t]][t]));
        res[p[t]][t] -= f;
        res[t][p[t]] += f;
        return f;
    }
    return 0;
}

int EdmondsKarp (int n, vector<iii>& edges, int s, int t, vvi& res) {
    // initialise adjacenty list and residuals adjacency matrix
    //vvi res(n,vi(n,0));
    res.resize(n,vi(n,0));
    vvi adj(n);
    for (iii e : edges) {
        res[e.second.first][e.second.second] += e.first;
        adj[e.second.first].push_back(e.second.second);
        adj[e.second.second].push_back(e.second.first);
    }
    // while we can add flow
    int addedFlow, maxFlow = 0;
    do {
        // save to p the BFS tree from s to t using only edges with residuals
        vi dist(res.size(), INF);
        dist[s] = 0;
        queue<int> q;
        q.push(s);
        vi p(res.size(), -1);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (u == t) break;
            for (int v : adj[u]) if (res[u][v] > 0 && dist[v] == INF) {
                    dist[v] = dist[u] + 1;
                    q.push(v);
                    p[v] = u;
                }
        }
        // add flow on the path between s to t according to p
        addedFlow = augment(res, s, t, p, INF);
        maxFlow += addedFlow;
    } while (addedFlow > 0);
    return maxFlow;
}

int main() {
    int n,m,s,t,u,v,c;
    cin>>n>>m>>s>>t;
    for(int i=0;i<m;i++){
        cin>>u>>v>>c;
        mymap[{u,v}]=c;
        edges.push_back({c,{u,v}});
    }
    vvi tmp;


    int flow= EdmondsKarp(n,edges,s,t,tmp);
    for(int i=0;i<tmp.size();++i){
        for(int j=0;j<tmp[i].size();j++){
            if(mymap.find({i,j})!=mymap.end()&& mymap[{i,j}]>tmp[i][j])
                ans.push_back({mymap[{i,j}]-tmp[i][j],{i,j}});
        }
    }
    int size=ans.size();
    cout<<n<<" "<<flow<<" "<<size<<endl;
    for(int i=0;i<size;i++){
        cout<<ans[i].second.first<<" "<<ans[i].second.second<<" "<<ans[i].first<<endl;
    }
    return 0;
}