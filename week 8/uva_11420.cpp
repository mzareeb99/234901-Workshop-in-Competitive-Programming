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


const int L = 0;
const int U = 1;

const int MAX_N = 65;
const int MAX_S = 65;

const int cdr=0;

ull dp[MAX_N+1][MAX_S+1][2];


int main(){
    fastIO;
    // dp[n][s][L] = dp[n-1][s][U] + dp[n-1][s-1][L]
    // dp[n][s][U] = dp[n-1][s][U] + dp[n-1][s][L]

    dp[1][0][U] = 1;
    dp[1][1][L] = 1;
    for (int i=1; i<=MAX_N; ++i){
        dp[i][0][U] = 1;
    }

    for (int n_i=2; n_i<=MAX_N; ++n_i){
        for (int s_i=0; s_i<=n_i; ++s_i){
             dp[n_i][s_i][L] = dp[n_i-1][s_i][U] + dp[n_i-1][s_i-1][L];
             dp[n_i][s_i][U] = dp[n_i-1][s_i][U] + dp[n_i-1][s_i][L];
        }
    }


    int n, s;
    while ((cin >> n >> s) && (n>=1 && s>=0)){
        cout << dp[n][s][U]+dp[n][s][L] << endl;
    }


    return 0;
}