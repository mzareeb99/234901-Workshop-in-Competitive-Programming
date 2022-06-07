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


int main() {
    fastIO;

    int n;
    cin >> n;
    vvull d(n, vull(n));
    for (int i=0; i<n; ++i){
        for (int j=0; j<n; ++j){
            cin >> d[i][j];
        }
    }

    priority_queue<iii, vector<iii>, greater<iii>> heap;
    for (int i=0; i<n; ++i){
        heap.push({d[0][i], {0, i}});
    }

    UnionFind uf(n);
    vector<bool> used(n, false);
    used[0] = true;

    vii sol;

    while (uf.sizes[uf.find(0)] != n){
        auto curr = heap.top();
        heap.pop();

        auto x = curr.second.first;
        auto y = curr.second.second;


        if (uf.find(x) != uf.find(y)){
            sol.emplace_back(x, y);
            uf.Union(x, y);
            if (!used[y]){
                used[y] = true;
                for (int i=0; i<n; ++i){
                    heap.push({d[y][i], {y, i}});
                }
            }
        }
    }

    for (const auto& p : sol){
        cout << p.first+1 << " " << p.second+1 << endl;
    }


    return 0;
}
