#include <vector>
#include <iostream>
using namespace std;
typedef long long ll;
typedef vector< vector<ll> > vvll;
int main(){
    int r,n;
    ll m;
    cin >>r>>n>>m;
    vvll dp(n+2,vector<ll>(n+2,0));
    dp[1][1] =1;
    for(int i = 2 ; i <= n;i++){
        dp[i][i] =1;
        for(int j =1;j<i;j++){
            dp[i][j]=(dp[i-1][j-1])%m;
            if(i==r) continue;
            dp[i][j] = ((dp[i-1][j-1])%m+j*dp[i-1][j]%m + (((j*(j+1))/2)*dp[i-1][j+1])%m)%m;
        }
    }
    cout<<dp[n][1]<<endl;
    return 0;
}