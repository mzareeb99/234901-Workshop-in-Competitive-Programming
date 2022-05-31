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

#include <iomanip>      // std::setprecision

const int maxx=6e5+9;
struct point{
    double x,y;
} a[maxx] , b[maxx];
ll ans1[maxx],ans2[maxx];

int main() {
    int N;
    double R,A,B;
    cin>>N>>R>>A>>B;
    double k=B/A;
    if (fabs(A)<0.001)
        k=1e18;
    for(int i=0;i<N;i++)
        cin>>a[i].x>>a[i].y;
    ll t1=-1,t2=-1;
    double a1,b1,c1,x1,y1;
    for(ll i=0;i<N;i++){
        if (fabs(k-1e18)<0.001){
            a1=1;
            b1= -2*a[i].y;
            c1= a[i].x*a[i].x+a[i].y*a[i].y-R*R;
        } else {
            a1=1+k*k;
            b1=-2*(a[i].x+k*a[i].y);
            c1= a[i].x*a[i].x+a[i].y*a[i].y-R*R;
        }
        if (b1*b1-4*a1*c1<0)
            continue;
        x1=(-b1- sqrt(b1*b1-4*a1*c1))/(2.0*a1);
        y1=(-b1+sqrt(b1*b1-4*a1*c1))/(2.0*a1);
        b[++t1].x= floor(x1*1000);
        b[t1].y= floor(y1*1000);
        ans1[++t2]= floor(x1*1000);
        ans1[++t2]= floor(y1*1000);
    }
    sort(ans1,ans1+t2+1);
    t2= unique(ans1,ans1+t2+1)-ans1-1;
    for(ll i=0;i<=t1;i++){
        ll tmp1= lower_bound(ans1,ans1+t2+1,b[i].x)-ans1;
        ll tmp2= lower_bound(ans1,ans1+t2+1,b[i].y)-ans1;
        ans2[tmp1]++;
        ans2[tmp2+1]--;
    }
    ll ans=ans2[0];
    for (ll i=1;i<=t2;i++){
        ans2[i]+=ans2[i-1];
        ans=max(ans,ans2[i]);
    }
    cout<<ans<<endl;
    return 0;
}
