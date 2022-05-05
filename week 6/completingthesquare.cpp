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
#define print(x) cout<<x<<endl
#define eps 1e-9
#define INF 1e9


int dst(pair<int,int> &p1,pair<int,int>&p2,pair<int,int>&p3){
    return abs(sqrt((p2.first - p3.first)*(p2.first - p3.first) + (p2.second - p3.second)*(p2.second - p3.second)) -
            sqrt((p2.first - p1.first)*(p2.first - p1.first) + (p2.second - p1.second)*(p2.second - p1.second))) < 1e-5;
}


int main() {
    fastIO;
    int x,y;
    int temp =3;
    vii vp;
    while(temp--){
        cin >>x>>y;
        vp.push_back({x,y});
    }
    //sort(vp.begin(),vp.end());
        x=y=0;
    if(dst(vp[1],vp[0],vp[2]) ) {
        x = vp[1].first+vp[2].first - vp[0].first;
        y = vp[1].second+vp[2].second - vp[0].second;
    }else if(dst(vp[0],vp[1],vp[2]) ) {
        x = vp[0].first+vp[2].first - vp[1].first;
        y = vp[0].second+vp[2].second - vp[1].second;
    }else if(dst(vp[0],vp[2],vp[1])){
        x = vp[0].first+vp[1].first - vp[2].first;
        y = vp[0].second+vp[1].second - vp[2].second;
    }
    cout<<x<<" "<<y<<" "<<endl;
    return 0;
}
