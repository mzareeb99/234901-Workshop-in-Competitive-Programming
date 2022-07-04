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


const int MAX_WEIGHT = 20;


int main(){
    fastIO;

    int TC;
    cin >> TC;

    for (int tc=1; tc<=TC; ++tc){
        int n;
        cin >> n;
        vi cs(n);
        for (int i=0; i<n; ++i){
            cin >> cs[i];
        }
        int cs_sum = accumulate(cs.begin(), cs.end(), 0);

        const int max_kid_weight = MAX_WEIGHT * n;
        vector<vector<vector<bool>>> dp(n+1, vector<vector<bool>>(max_kid_weight+1, vector<bool>(max_kid_weight+1, false)));
        // dp[i][j][k] = is it possible to get to configuration: i first candies, first kid has j, second kid his k.
        // dp[i][j][k] = dp[i-1][j-cs[i]][k] || dp[i-1][j][k-cs[i]] || dp[i-1][j][k]
        // dp[0][0][0] = true

        dp[0][0][0] = true;
        for (int i=1; i<=n; ++i){
            for (int j=0; j<=max_kid_weight; ++j){
                for (int k=0; k<=max_kid_weight; ++k){
                    dp[i][j][k] = dp[i-1][j][k];
                    if (j >= cs[i-1] && dp[i-1][j-cs[i-1]][k]){
                        dp[i][j][k] = true;
                    }
                    if (k >= cs[i-1] && dp[i-1][j][k-cs[i-1]]){
                        dp[i][j][k] = true;
                    }
                }
            }
        }

        int best = 1e9;
        for (int j=0; j<=max_kid_weight; ++j){
            for (int k=0; k<= max_kid_weight; ++k){
                if (dp[n][j][k]){
                    best = min(best, max(j, max(k, cs_sum-j-k)) - min(j, min(k, cs_sum-j-k)));
                }
            }
        }
        cout << "Case " << tc << ": " << best << endl;
    }

    return 0;
}
