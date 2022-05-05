#include <algorithm>
#include <cmath>
#include <cstdio>
#include <deque>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;
typedef pair<long, long> pii;
typedef pii ii;
typedef vector<ii> vii;
typedef vector<pair<long, long>> vll;

#define fastIO ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
long dis(ii &p1,ii&p2){
    return (p2.first - p1.first)*(p2.first - p1.first) + (p2.second - p1.second)*(p2.second - p1.second);
}
long dot(ii &o,ii &a,ii &b){
    return (a.first - o.first)*(b.first-o.first) + (a.second - o.second)*(b.second-o.second);
}
long cross(ii& o,ii& a,ii& b){
    return (a.first - o.first)*(b.second-o.second) - (a.second - o.second)*(b.first-o.first);
}
 double fun(ii &a, ii &b,ii &o) {
    int ret = dis(a, b);
    double d = sqrt(min(dis(a, o), dis(b, o)));
    if (dot(a, b, o) < ret && dot(b, a, o) < ret) {
        return min(d, fabs((double) (cross(a, o, b) / sqrt(dis(a, b)))));
    }
    return d;
}

int main() {
   fastIO;
   int t;
   cin>>t;
   while(t--){
       vii v (4);
       for(int i=0 ;i < 4;i++)
            cin>>v[i].first>>v[i].second;
        if(cross(v[0],v[1],v[2])*cross(v[0],v[1],v[3]) < 0 &&
          cross(v[2],v[3],v[0])*cross(v[2],v[3],v[1]) < 0)
            printf("0.00\n");
        else{
           double tmp =fun(v[0],v[1],v[2]);
            tmp = min(tmp,fun(v[0],v[1],v[3]));
            tmp = min(tmp,fun(v[2],v[3],v[0]));
            tmp = min(tmp,fun(v[2],v[3],v[1]));
            printf("%0.2f\n",tmp);
        }
   }
    return 0;
}
