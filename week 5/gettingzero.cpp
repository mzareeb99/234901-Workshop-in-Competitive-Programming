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
typedef vector<vi> vvi;
typedef vector<vll> vvll;
typedef vector<vull> vvull;
typedef pair<int, int> pii;
typedef vector<pii> vii;
typedef vector<vii> vvii;
typedef priority_queue<int> max_iheap;
typedef priority_queue<ll> max_llheap;
typedef priority_queue<ull> max_ullheap;
typedef priority_queue<int, vi, greater<int>> min_iheap;
typedef priority_queue<int, vll, greater<ll>> min_llheap;
typedef priority_queue<int, vull, greater<ull>> min_ullheap;
#define fastIO ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)

const int N = 32768;


int main(){
    fastIO;
    vector<ull> v(N);
    vector<bool> visited(N, false);
    v[0] = 0;
    visited[0] = true;
    queue<int> q;
    q.push(0);
    while (!q.empty()){
        int u = q.front();
        q.pop();
        if (!visited[(u+N-1)%N]){
            visited[(u+N-1)%N] = true;
            v[(u+N-1)%N] = v[u]+1;
            q.push((u+N-1)%N);
        }
        if (!(u&1)){
            if (!visited[u/2]){
                visited[u/2] = true;
                v[u/2] = v[u]+1;
                q.push(u/2);
            }
            if (!visited[(u+N)/2]){
                visited[(u+N)/2] = true;
                v[(u+N)/2] = v[u]+1;
                q.push((u+N)/2);
            }
        }
    }

    int n;
    int curr;
    cin >> n;
    for (int i=1; i<n; ++i){
        cin >> curr;
        cout << v[curr] << " ";
    }
    cin >> curr;
    cout << v[curr] << endl;


    return 0;
}