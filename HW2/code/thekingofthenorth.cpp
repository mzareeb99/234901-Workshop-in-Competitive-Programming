#include <iostream>
#include <vector>
#include <queue>
using namespace std;
typedef pair<int,int> ii;
typedef pair<int,ii> iii;
typedef vector<ii> vii;
typedef vector<vii> vvii;
typedef vector<int> vi;
typedef vector<vi> vvi;




const int INF = 1e9;

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
// input: number of nodes (n), all nodes are between 0 and n-1,
//        edges v1->v2 of the form (weight,(v1,v2)), source (s) and target (t).
// output: max flow from s to t over the edges.
// time: O(VE^2) and O(EF).
int EdmondsKarp (int n, vector<iii>& edges, int s, int t) {
    // initialise adjacenty list and residuals adjacency matrix
    vvi res(n,vi(n,0));
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
struct FlowEdge {
    int v, u;
    long long cap, flow = 0;
    FlowEdge(int v, int u, long long cap) : v(v), u(u), cap(cap) {}
};

struct Dinic {
    const long long flow_inf = 1e18;
    vector<FlowEdge> edges;
    vector<vector<int>> adj;
    int n, m = 0;
    int s, t;
    vector<int> level, ptr;
    queue<int> q;

    explicit Dinic(int n) : n(n),s(INF),t(INF) {
        adj.resize(n);
        level.resize(n);
        ptr.resize(n);
    }

    void add_edge(int v, int u, long long cap) {
        edges.emplace_back(v, u, cap);
        edges.emplace_back(u, v, 0);
        adj[v].push_back(m);
        adj[u].push_back(m + 1);
        m += 2;
    }

    bool bfs() {
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int id : adj[v]) {
                if (edges[id].cap - edges[id].flow < 1)
                    continue;
                if (level[edges[id].u] != -1)
                    continue;
                level[edges[id].u] = level[v] + 1;
                q.push(edges[id].u);
            }
        }
        return level[t] != -1;
    }

    long long dfs(int v, long long pushed) {
        if (pushed == 0)
            return 0;
        if (v == t)
            return pushed;
        for (int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
            int id = adj[v][cid];
            int u = edges[id].u;
            if (level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1)
                continue;
            long long tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
            if (tr == 0)
                continue;
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }

    long long flow() {
        long long f = 0;
        while (true) {
            fill(level.begin(), level.end(), -1);
            level[s] = 0;
            q.push(s);
            if (!bfs())
                break;
            fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(s, flow_inf)) {
                f += pushed;
            }
        }
        return f;
    }
};
int R,C;
bool in_range(int x,int y){
    if(x<0 || y<0 || x>=R || y>=C) return false;
    return true;
}


int main() {

    cin >> R >>C;
    Dinic netflow(2*R*C+1) ;
    //vvi kingdom_map(R,vi(C,0));
    for(int i=0;i<R;i++){
        for(int j=0;j<C;j++){
            int cap;
            cin >> cap;
            netflow.add_edge(i*C+j,i*C+j+R*C,cap);
            for(int dx=-1;dx<=1;dx++){
                for(int dy =-1 ;dy<=1;dy++){
                    int x =i+dx, y =j+dy;
                    if(abs(dx)==abs(dy) || !in_range(x,y)) continue;
                    netflow.add_edge(i*C+j+R*C,x*C+y,INF);
                }
            }
        }
    }
    for(int i=0;i<R;i++){
        netflow.add_edge(2*R*C,i*C,INF);
        netflow.add_edge(2*R*C,i*C+C-1,INF);
    }
    for(int j=0;j<C;j++){

        netflow.add_edge(2*R*C,C*(R-1)+j,INF);
    }
    int castle_x,castle_y;
    cin >> castle_x >> castle_y;
    netflow.s=2*R*C;
    netflow.t=castle_x*C+castle_y+R*C;
    cout << netflow.flow() << endl;



    return 0;
}
