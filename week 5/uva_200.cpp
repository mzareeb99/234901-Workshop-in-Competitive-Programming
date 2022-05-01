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
typedef pair<int,ii> iii;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef set<int> si;
typedef vector<si> vsi;
typedef vector< vector<int> > vvi; // unweighted graph
typedef vector< vector< pair<int,int> > > vvii; // weighted graph
#define print(x) cout<<x<<endl
#define eps 1e-7
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

map<char, vector<char> > adjList;
map<char, int> flags;

void dfsChr(vector<char>&order,char c)
{
    flags[c] = VISITED;
    for (char v : adjList[c])
    {
        if (flags[v] == UNVISITED)
            dfsChr(order, v);
    }
    order.push_back(c);
}

int main()
{
    string s1, s;
    cin >> s1;
    while (cin >> s) {
        if (s == "#")
            break;

        s1 += string(20 - s1.size(), ' ');
        s += string(20 - s.size(), ' ');
        for (int i = 0; i < 20; i++)
            if (s[i] != s1[i]) {
                adjList[s1[i]].push_back(s[i]);
                flags[s1[i]] = UNVISITED;
                flags[s[i]] = UNVISITED;
                break;
            }
        s1 = s;
    }
    vector<char> order;
    for (auto &i: adjList)
        if (flags[i.first] == UNVISITED)
            dfsChr(order, i.first);
    for (int i = (int) order.size() - 1; i >= 0; --i)
        if (order[i] != ' ')
            cout << order[i];
    cout << endl;
    return 0;
}