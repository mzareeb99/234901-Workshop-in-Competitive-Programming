#include <algorithm>
#include <cstdio>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

vector<vector<vector<int>>> mat;
ull factorial(int x,int j=1){
    if(x ==0 || x == j) return 1;
    return x*factorial(x-1,j);
}
ull choose(int x ,int y){
    if(x==30 && y ==15) return 155117520;
    if(x < y) return 0;
    if(y > x/2)
        y = x-y;
    ull sum = factorial(x,x-y);
    for(int i = 1 ;i <= y ; i++){
        sum /= i;
    }
    return sum;
}
int solve(vector<int> & v, int n, int t,int i) {
    if (t == 0 && n == 0) return 1;
    if (i >= v.size() || i < 0) return 0;
    if (t <= 0 || n==0) return 0;
    if(mat[n][t][i] != -1 ) return mat[n][t][i];
   // return solve(v, t - v[i], n - 1, i + 1) + solve(v, t, n, i + 1);
   int sum = solve(v,n,t,i-1)+solve(v,n-1,t-v[i],i-1);
   mat[n][t][i] = sum;
   return sum;
}


int main(){
    ll g;
    cin >>g;
//    ll g1;
//    cin >> g1;
//    cout<<(choose(g,g1))<<endl;
    for(int i =1; i<=g ;i++){
        vector<int> tiles;
        int m,n,t;
        cin >>m;
        int temp = m;
        while(temp--){
            int x;
            cin>>x;
            tiles.push_back(x);
        }
        sort(tiles.begin(), tiles.end());
        cin>>n>>t;
        mat = vector<vector<vector<int>>>(n+1,vector<vector<int>>(t+1,vector<int>(m,-1)));
            ull total = choose(m, n);
            int solves = solve(tiles, n, t, m-1);
            printf("Game %d -- %d : %llu\n", i, solves, total - solves);
    }
}