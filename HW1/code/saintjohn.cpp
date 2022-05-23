//
//  main.cpp
//  convexhull
//
//  Created by Yufei Zheng on 09/05/2018.
//  Copyright Â©️ 2018 Yufei Zheng. All rights reserved.
//

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
#include <unordered_map>
#include <unordered_set>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<ull> vull;
typedef vector<bool> vb;
typedef vector<vi> v2i;
typedef priority_queue<int> max_iheap;
typedef priority_queue<ll> max_llheap;
typedef priority_queue<ull> max_ullheap;
typedef priority_queue<int, vi, greater<int>> min_iheap;
typedef priority_queue<int, vll, greater<ll>> min_llheap;
typedef priority_queue<int, vull, greater<ull>> min_ullheap;
typedef vector<pair<double,double>> vpd;
typedef pair<int,int> ii;
typedef pair<double,double> dd;
typedef pair<dd,double> ddd;
typedef pair<int,ii> iii;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef set<int> si;
typedef vector<si> vsi;
typedef vector< vector<int> > vvi; // unweighted graph
typedef vector< vector< pair<int,int> > > vvii; // weighted graph
#define fastIO ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)

#define print(x) cout<<x<<endl
#define EPS 1e-9
#define MAX_SIZE 100

using namespace std;
typedef pair<double,double> dp;

struct PT
{
    double x,y;
    PT(){}
    PT (double x1,double y1) : x(x1),y(y1){}
    bool operator < (const PT& _p) const
    {
        if (fabs(x - _p.x) > EPS) {
            return (x < _p.x);
        } else {
            return (y < _p.y);
        }
    }

    bool operator == (const PT& _p) const
    {
        if ((fabs(x - _p.x) < EPS ) && (fabs(y - _p.y) < EPS )) {
            return true;
        } else {
            return false;
        }
    }

};


// check p3 (leftmost) -> p2 -> p1 (rightmost) left turn (not right turn)
bool left(PT& p1, PT& p2, PT& p3)
{
    long double cross = (p2.x - p3.x) * (p1.y - p3.y) - (p2.y - p3.y) * (p1.x - p3.x);

    if (fabs(cross) <= EPS)
        return true;    // to delete p2
    if (cross > 0)
        return true;
    return false;
}
double norm(dp v){
    return v.first*v.first+v.second*v.second;
}



double angle(PT a, PT o, PT b){
    dp oa = {a.x-o.x,a.y-o.y};
    dp ob= {b.x-o.x,b.y-o.y};
    double dot = oa.first*ob.first+oa.second*ob.second;
    return acos(dot / sqrt(norm(oa)* norm(ob)));
}

vector<PT> convexhull (vector<PT> Points) {
    PT p;
    sort(Points.begin(), Points.end());
    stack<PT> stk_up;
    stk_up.push(Points[0]);
    stk_up.push(Points[1]);
    for (int i=2; i<Points.size(); i++) {
        while ((stk_up.size() >= 2)) {
            PT p2, p3;
            p2 = stk_up.top();
            stk_up.pop();
            p3 = stk_up.top();
            if (!left(Points[i], p2, p3)){
                stk_up.push(p2);
                break;
            }
        }
        stk_up.push(Points[i]);
    }
    // lower hull
    for (int i=0; i<Points.size(); i++) {
        Points[i].x = -Points[i].x;
        Points[i].y = -Points[i].y;
    }
    sort(Points.begin(), Points.end());
    stack<PT> stk_low;
    stk_low.push(Points[0]);
    stk_low.push(Points[1]);
    for (int i=2; i<Points.size(); i++) {
        while ((stk_low.size() >= 2)) {
            PT p2, p3;
            p2 = stk_low.top();
            stk_low.pop();
            p3 = stk_low.top();
            if (!left(Points[i], p2, p3)){
                stk_low.push(p2);
                break;
            }
        }
        stk_low.push(Points[i]);
    }

    // print convex hull - cw order from leftmost point
    vector<PT> CH;
    stk_low.pop();
    while (!stk_low.empty()) {
        p = stk_low.top();
        p.x = -p.x;
        p.y = -p.y;
        CH.push_back(p);
        stk_low.pop();
    }
    stk_up.pop();
    while (!stk_up.empty()) {
        CH.push_back(stk_up.top());
        stk_up.pop();
    }
    reverse(CH.begin(), CH.end());  // ccw -> cw
    return CH;

}



bool isInside (vector<PT> points, PT p){
    auto it1 = points.begin();
    auto it2= points.end()-1;
    PT p1,p2;
    p1 = *it1;
    p2 = *it2;
    reverse(points.begin()+1,points.end());
    auto high = lower_bound(it1,it2++,p,[p1,p2](PT x, PT y){
        if (p1==x || p2==x)
            return true;
        double s1= angle(p2,p1,x);
        double s2=angle(p2,p1,y);
        return s1<s2;
    });
    auto low =high-1;
    if(high==points.end())
        return false;
    vector<PT> v {*low,*high, p, *it1};
    vector<PT> tmp = convexhull(v);
    return find(tmp.begin(),tmp.end(),p)==tmp.end();
}

int main() {
    fastIO;
    int L;
    cin>>L;
    vector<PT> large;
    for(int i=1;i<=L;++i){
        PT p;
        cin>>p.x>>p.y;
        large.push_back(p);
    }
    large = convexhull(large);
    int S;
    long long count = 0 ;
    cin >>S;
    while (S--){
        PT p;
        cin>>p.x>>p.y;
        if (isInside(large,p)) {
            count++;
        }
    }
    cout<<count<<endl;
    return 0;
}
