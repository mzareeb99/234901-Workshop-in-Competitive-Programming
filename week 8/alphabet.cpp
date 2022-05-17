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
string s;
string alpha="abcdefghijklmnopqrstuvwxyz";
int dp[100][50];
int len;


int dpsolve(int i, int j){
    if (i>=len || j>=26)
        return 0;
    if (dp[i][j]!=-1)
        return dp[i][j];
    if (s[i]==alpha[j])
        return dp[i][j]= max(dpsolve(i+1,j), 1+dpsolve(i+1,j+1));
    else
        return dp[i][j]= max(dpsolve(i,j+1), dpsolve(i+1,j));
}



int main() {
    cin>>s;
    len= s.size();
    memset(dp, -1, sizeof dp);
    cout<<26- dpsolve(0,0)<<endl;
}
