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
typedef priority_queue<int> max_iheap;
typedef priority_queue<ll> max_llheap;
typedef priority_queue<ull> max_ullheap;
typedef priority_queue<int, vi, greater<int>> min_iheap;
typedef priority_queue<int, vll, greater<ll>> min_llheap;
typedef priority_queue<int, vull, greater<ull>> min_ullheap;
typedef vector<pair<double,double>> vpd;
#define print(x) cout<<x<<endl
#define eps 1e-7
#define INF 1e9

double f(vpd &v,double x ){
    int f = v.size()-1;
    double r  = INF ;
    for( int i = 0 ; i < f; ++i ){
        if(  x*v[i].first+v[i].second < r )
            r = (x*v[i].first+v[i].second);
    }
    return r- (x*v[f].first+v[f].second);
}
double ternarySearch(vpd &v,double l , double r ){ // e error
    if( r - l  < 0.001 )
        return (r+l)/2;
    double lt = ( 2*l + r )/3 ;
    double rt = ( l + 2*r )/3 ;
    if( ( f(v,lt) < f(v,rt) )  )
        return ternarySearch(v,lt , r  );
    return ternarySearch(v, l , rt );
}
int main() {
    double t ,  r , k ;
    int n;
    while( cin >> t>>n ){
        vpd v;
        for( int i = 0 ; i < n ; ++i  ){
            cin >> r >> k;
            v.push_back({(k-r)/(k*r) , t/k });
        }
        double d = ternarySearch(v,0 ,t );
        double x = f(v,d);
        if( x > -eps )
            printf("The cheater can win by %.0lf seconds with r = %.2lfkm and k = %.2lfkm.\n", (fabs(x)*3600) , d , t-d);
        else
            puts("The cheater cannot win.");
    }
    return 0;
}