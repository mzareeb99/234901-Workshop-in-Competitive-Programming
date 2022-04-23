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
typedef pair<int, int> pii;
typedef priority_queue<int> max_iheap;
typedef priority_queue<ll> max_llheap;
typedef priority_queue<ull> max_ullheap;
typedef priority_queue<int, vi, greater<int>> min_iheap;
typedef priority_queue<int, vll, greater<ll>> min_llheap;
typedef priority_queue<int, vull, greater<ull>> min_ullheap;

#define print(x) cout<<x<<endl

int fub(ll n,int b){
    if(b < 2) return 0;
    vector<int> vec(2,1);
    int temp = 2;
    do{
           vec.push_back((1 + vec[temp-1] + vec[temp-2])%b);
           temp++;
    }while(vec[temp-1] != 1 || vec[temp-2] != 1);
    vec.pop_back(); //delete the 1's in the  back
    vec.pop_back();
    temp-=2;
    return vec[n%temp];
}

int main(){
    ll n;
    int b;
    cin>>n>>b;
    int x = 0;
    while(n!=0 || b!=0) {
        printf("Case %d: %lld %d %d\n", ++x, n, b, fub(n, b));
        cin>>n>>b;
    }
}