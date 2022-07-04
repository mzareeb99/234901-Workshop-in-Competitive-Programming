#include <iostream>
#include <vector>
#include <map>
#include <stack>

const int INF = 1e9;

using namespace std;

typedef pair<int,int> ii;
typedef pair<int,ii> iii;
typedef vector<int> vi;
typedef vector<vi> vvi;


int augment(map<ii,int>& res, int s, int t, const vi& p, int minEdge) {
    // traverse the path from s to t according to p.
    // change the residuals on this path according to the min edge weight along this path.
    // return the amount of flow that was added.
    if (t == s) {
        return minEdge;
    } else if (p[t] != -1) {
        int f = augment(res, s, p[t], p, min(minEdge, res[ii(p[t],t)]));
        res[ii(p[t],t)] -= f;
        res[ii(t,p[t])] += f;
        return f;
    }
    return 0;
}

// input: number of nodes (n), all nodes are between 0 and n-1,
//        edges v1->v2 of the form (weight,(v1,v2)), source (s) and target (t).
// output: max flow from s to t over the edges.
// time: O(VE^2) and O(EF).
int EdmondsKarp (int n, vector<iii>& edges, int s, int t) {
    // initialise adjacenty list and residuals adjacency matrix
    map<ii,int> res {};
    vvi adj(n);
    for (iii e : edges) {
        res[ii(e.second.first,e.second.second)] += e.first;
        adj[e.second.first].push_back(e.second.second);
        adj[e.second.second].push_back(e.second.first);
    }
    // while we can add flow
    int addedFlow, maxFlow = 0;
    do {
        // save to p the BFS tree from s to t using only edges with residuals
        vi dist(res.size(), INF);
        dist[s] = 0;
        stack<int> q;
        q.push(s);
        vi p(res.size(), -1);
        while (!q.empty()) {
            int u = q.top(); q.pop();
            if (u == t) break;
            for (int v : adj[u]) if (res[ii(u,v)] > 0 && dist[v] == INF) {
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
    int num_tests;
    cin >> num_tests;
    while(num_tests--){
        int n;
        cin >> n;
        int i,g, num_steps;
        cin >> i >> g >> num_steps;
        vector<iii> edges;
        --i;
        edges.emplace_back(g,ii(n*(num_steps+1)+1,i*(num_steps+1)));
        int m;
        cin >> m;
        for(int j=0; j<m; ++j){
            int x;
            cin >> x;
            --x;
            edges.emplace_back(INF,ii(x*(num_steps+1)+num_steps,n*(num_steps+1)));
        }
        int r;
        cin >> r;
        for(int j=0; j<r; ++j){
            int a,b,p,t;
            cin >> a >> b >> p >> t;
            --a;--b;
            for(int curr_time=0; curr_time+t<=num_steps; ++curr_time)
                edges.emplace_back(p,ii(a*(num_steps+1)+curr_time, b*(num_steps+1)+curr_time+t));
        }

        for(int j=0; j<n; ++j){
            for(int curr_time=0; curr_time+1<=num_steps; ++curr_time){
                edges.emplace_back(INF,ii(j*(num_steps+1)+curr_time, j*(num_steps+1)+curr_time+1));
            }
        }
        int ans = EdmondsKarp(n*(num_steps+1)+2, edges, n*(num_steps+1)+1, n*(num_steps+1));
        cout <<  ans << endl;

    }
}


