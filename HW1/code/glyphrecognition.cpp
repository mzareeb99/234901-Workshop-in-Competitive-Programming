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
#define pi acos(-1.0)



int main() {
    int num;
    cin>>num;
    vector<pair<double,double>> coords(1003);
    double x,y;
    for(int i=0;i<num;i++){
        cin>>x>>y;
        coords[i] ={sqrt(x*x+y*y),atan(y/x)*180/pi};
        coords[i].second = x >= 0? coords[i].second+=360 : coords[i].second+=180;
    }
    double max_score=0;
    int id;
    for(int i=3;i<=8;++i){
        double deg=360.0/i * pi/180.0;
        double _max=-1;
        double _min=1e9;
        for(int j=0;j<num;j++){
            double tmp= (coords[j].second-(int)(coords[j].second/(360.0/i))*360.0/i )* (pi/180.0);
            double len= (cos(tmp-deg/2)*(coords[j].first))/(cos(deg/2.0));
            _min= min(_min,len);
            _max= max(_max,len);
        }
        double temp= (_min*_min)/(_max*_max);
        max_score = temp>max_score? temp : max_score;
        if(temp>=max_score) {
            id=i;
        }
    }
    cout<<setprecision(10)<<fixed<<id <<' '<< max_score<<endl;
    return 0;
}
