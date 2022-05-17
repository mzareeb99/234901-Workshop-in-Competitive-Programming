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


const int INF = numeric_limits<int>::max();
const int cdr=10;

int f(int v, int visited, vvi& memo, const vvi& g, int n) {
    if (memo[v][visited] != -1) return memo[v][visited];
    if (visited == (1<<n)-1) return g[v][0];
    int ans = INF;
    for (int u = 0; u < n; u++)
        if (!(visited & (1<<u)))
            ans = min(ans, g[v][u] + f(u,visited|(1<<u), memo, g, n));
    return memo[v][visited] = ans;
}


int main(){
    fastIO;

    int TC;
    cin >> TC;

    while (TC--){
        int x, y;
        cin >> x >> y;
        pii start;
        cin >> start.first >> start.second;

        int beepers_num;
        cin >> beepers_num;

        vvi g(beepers_num+1, vi(beepers_num+1, 0));
        vii beepers(beepers_num);
        for (int i=0; i<beepers_num; ++i){
            cin >> beepers[i].first;
            cin >> beepers[i].second;
        }
        for (int i=1; i<=beepers_num; ++i){
            for (int j=1; j<=beepers_num; ++j){
                g[i][j] = abs(beepers[i-1].first-beepers[j-1].first) + abs(beepers[i-1].second-beepers[j-1].second);
            }
        }

        for (int j=1; j<=beepers_num; ++j){
            g[0][j] = g[j][0] = abs(start.first-beepers[j-1].first) + abs(start.second-beepers[j-1].second);
        }

        vvi memo(beepers_num+1, vi((1<<(beepers_num+2))-1,-1));

        cout << f(0, 1, memo, g, beepers_num+1) << endl;

    }

    return 0;
}

