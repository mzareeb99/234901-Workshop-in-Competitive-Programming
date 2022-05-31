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
#include <iomanip>      // std::setprecision


double distance(ii p1,ii p2){
    return sqrt((p1.first-p2.first)*(p1.first-p2.first)+(p1.second-p2.second)*(p1.second-p2.second));
}

int main() {
    map<int,pair<int,int>> mymap;
    int s[3][3];
    double sum=0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            cin>>s[i][j];
            mymap[s[i][j]]= ii (i,j);
        }
    }
    ii p=mymap[1];
    for(auto it:mymap){
        sum+= distance(it.second,p);
        p= it.second;
    }

    cout<<fixed<<setprecision(10)<<sum<< endl;

    return 0;
}
