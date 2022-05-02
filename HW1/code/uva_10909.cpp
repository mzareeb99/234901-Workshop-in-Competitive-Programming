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


vector<bool> lucky_nums;


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



class Graph {
public:
    vector<int> vec;
    int size;
    Graph(){
        size = 2097152;
        vec = vector<int>(size * 2, 0);
        for (int bit = 1; bit < size; bit += 2) {
            modify(bit, 1);
        }
    }
    void modify(int p, int value) {
        for (vec[p += size] = value; p > 1; p >>= 1) {
            vec[p>>1] = vec[p] + vec[p^1];
        }
    }
    int find_num_by_index(int index) {
        int i = 0;
        int current_node = 1;
        while (current_node < size) {
            if (vec[current_node * 2] + i >= index) {
                current_node *= 2;
            }
            else {
                i += vec[current_node * 2];
                (current_node *= 2)++;
            }
        }
        return current_node - size;
    }

    int get_num_of_bits_on() {
        return vec[1];
    }
};


void calc_lucky_nums() {
    lucky_nums[1] = true;
    Graph graph;
    for (int i = 2;
         i <= graph.get_num_of_bits_on();
         i++) {

        int next_lucky = graph.find_num_by_index(i);
        if (next_lucky >= lucky_nums.size()) {
            continue;
        }
        lucky_nums[next_lucky] = true;
        for (int j = next_lucky;
             j < graph.get_num_of_bits_on();
            j += (next_lucky - 1)) {

            int next_to_remove = graph.find_num_by_index(j);
            graph.modify(next_to_remove, 0);
        }
    }
}
int main() {
    lucky_nums = vector<bool>(MAX_SIZE,false);
    calc_lucky_nums();
    int next_num;
    while (cin >> next_num) {
        if (next_num % 2 == 1) {
            printf("%d is not the sum of two luckies!\n", next_num);
        }
        else {
            for (int i = next_num / 2; i > 0; i--) {
                if (lucky_nums[i] && lucky_nums[next_num - i]) {
                    printf("%d is the sum of %d and %d.\n", next_num, i, next_num - i);
                    break;
                }
            }
        }
    }
    return 0;
}