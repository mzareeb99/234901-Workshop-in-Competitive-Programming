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

struct matrix{
    int mat[101][101];
};

matrix mat1,mat2;
int n;

matrix mult(matrix m1, matrix m2){
    matrix m3;
    memset(m3.mat, 0 , sizeof m3.mat);
    for(int i=1;i<=n;i++){
        for(int j=1; j<=n; j++){
            for(int k=1; k<=n; k++){
                m3.mat[i][j] += m1.mat[i][k]*m2.mat[k][j];
                m3.mat[i][j]%=10000;
            }
        }
    }
    return m3;

}
matrix exp(int x){
    if (x==0)
        return mat2;
    if(x==1)
        return mat1;
    if (x&1)
        return mult(mat1,exp(x-1));
    matrix m3= exp(x/2);
    return mult(m3,m3);

}

int main() {
    int l,s,t;
    for (int i=0;i<101;i++)
        mat2.mat[i][i]=1;
    while (scanf("%d%d", &n,&l)==2){
        cin>>s>>t;
        memset(mat1.mat,0,sizeof mat1.mat);
        for(int i=1;i<n+1;i++){
            for (int j = 0;  j<4 ; j++) {
                int x;
                cin>>x;
                mat1.mat[i][x]++;

            }
        }
        matrix m3= exp(l);
        cout<< m3.mat[s][t]<<endl;
    }
    return 0;
}