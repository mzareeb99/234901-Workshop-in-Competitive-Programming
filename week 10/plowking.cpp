#include <iostream>
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
#include <vector>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pair<double,double>> vpd;
typedef pair<int,int> ii;
typedef pair<double,double> dd;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef set<int> si;
typedef vector<si> vsi;
typedef vector< vector<int> > vvi; // unweighted graph
typedef vector< vector< pair<int,int> > > vvii; // weighted graph
using namespace std;


 ll n,m,sum;
int main() {
    cin>>n;
   cin >>m;
    while (m){
        if (m>((n-1)*(n-2))/2){
            sum+=((n-1)*(n-2))/2+1;
            m=((n-1)*(n-2));
            n--;
        } else{
            sum+=m;
            m--;
            n--;
        }
    }
    cout<<sum<<endl;
}