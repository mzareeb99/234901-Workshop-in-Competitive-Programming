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
typedef pair<int, int> pii;
typedef vector<vi> vvi;
typedef priority_queue<int> max_iheap;
typedef priority_queue<ll> max_llheap;
typedef priority_queue<ull> max_ullheap;
typedef priority_queue<int, vi, greater<int>> min_iheap;
typedef priority_queue<int, vll, greater<ll>> min_llheap;
typedef priority_queue<int, vull, greater<ull>> min_ullheap;
typedef vector<pair<double,double>> vpd;
int INF= 1e6 ;


ll dp[255][255];
int l[255], s[255],c[255];

int main() {
    int n,m;
    ll k,r;
    cin>>n>>m>>k>>r;
    memset(dp,INF ,sizeof dp);
    dp[1][1]=0;
    for (int i=1;i<=n; i++){
        cin>>l[i];
    }
    for (int i=1; i<=n-1;i++)
        cin>>s[i]>>c[i];
    s[n]=0;
    c[n]=0;
    for(int i=2;i<=n+1;i++) {
        for (int j = 1; j <= m; j++) {
            for (int x = 1; x <= m; x++) {
                if (abs(j - x) * k <= l[i - 1]) {
                    int val = abs(j - x) * r;
                    dp[i][j] = min(dp[i][j], dp[i - 1][x] + l[i - 1] + s[i - 1] + c[i - 1] * j + val);
                }
            }
        }
    }
    cout<<dp[n+1][1]<<endl;
}
