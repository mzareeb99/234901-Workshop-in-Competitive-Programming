#include <iostream>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <functional>
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
#define EPS 1e-9


struct PT
{
    double x,y;

    // compare the lexicographic order of 2 points
    // first compare x, if 2 x's are equal, compare y
    bool operator < (const PT& _p) const
    {
        if (fabs(x - _p.x) > EPS) {
            return (x < _p.x);
        } else {
            return (y < _p.y);
        }
    }
};

struct segment {
    PT p1,p2;
};

PT line_intersect(segment s1, segment s2){
    PT A = s1.p1;
    PT B = s1.p2;
    PT C = s2.p1;
    PT D = s2.p2;
    double a1 = B.y - A.y;
    double b1 = A.x - B.x;
    double c1 = a1*(A.x) + b1*(A.y);

    // Line CD represented as a2x + b2y = c2
    double a2 = D.y - C.y;
    double b2 = C.x - D.x;
    double c2 = a2*(C.x)+ b2*(C.y);

    double determinant = a1*b2 - a2*b1;

    if (determinant == 0)
    {
        // The lines are parallel. This is simplified
        // by returning a pair of FLT_MAX
        return {0, 0};
    }
    else
    {
        double x = (b2*c1 - b1*c2)/determinant;
        double y = (a1*c2 - a2*c1)/determinant;
        return {x, y};
    }

}

bool point_in_segment(PT p, segment s){
    double s_x_min = min(s.p1.x, s.p2.x);
    double s_x_max = max(s.p1.x, s.p2.x);
    double s_y_min = min(s.p1.y, s.p2.y);
    double s_y_max = max(s.p1.y, s.p2.y);
    return  p.x > s_x_min - EPS && p.x < s_x_max + EPS &&
            p.y > s_y_min - EPS && p.y < s_y_max + EPS;
}

bool PointOnLine(PT p, segment l) {
    if (fabs(l.p1.x - l.p2.x) < EPS) {
        return fabs(l.p1.x-p.x) < EPS;
    }
    if (fabs(l.p1.y - l.p2.y) < EPS) {
        return fabs(l.p1.y-p.y) < EPS;
    }
    double m = (l.p1.y-l.p2.y) / (l.p1.x - l.p2.x);
    double m2 = (l.p1.y - p.y) / (l.p1.x - p.x);
    return fabs(m-m2) < EPS;
}

bool point_in_ray(PT p, segment r) {
    segment s2 = {p, r.p2};
    return !point_in_segment(r.p1, s2);
}

bool segment_intersect(segment s1, segment s2){
    PT p = line_intersect(s1, s2);
    return point_in_segment(p, s1) && point_in_segment(p, s2);
}

bool line_intersect_segment(segment s, segment l) {
    PT p = line_intersect(s, l);
    return point_in_segment(p, s);
}

bool ray_intersect_segment(segment s, segment ray) {
    PT p = line_intersect(s, ray);
    return point_in_segment(p, s) && point_in_ray(p, ray);
}

PT randomPT(){
    PT p;
    p.x=random() % 100000;
    p.y=random() % 100000;
    return p;
}

int main() {
    int test;
    while (cin>>test&&test!=0){
        vector<PT> Points;
        while (test--) {
            PT p1;
            cin>>p1.x;
            cin>>p1.y;
            Points.push_back(p1);
        }
        int point;
        cin>>point;

        while (point--){
            PT p;
            cin>>p.x;
            cin>>p.y;
            int success = 0;
            bool point_on_polygon = false;
            for (int j=0; j<Points.size(); j++) {
                segment s = {Points[j], Points[(j+1)%Points.size()]};
                if (point_in_segment(p, s) && PointOnLine(p, s)) {
                    cout << "on" << endl;
                    point_on_polygon = true;
                    break;
                }
            }
            if (point_on_polygon) continue;
            for (int i = 0; i < 3; i++) {
                PT p2=randomPT();
                segment ray = {p,p2};
                int num_intersections = 0;
                for (int j=0; j<Points.size(); j++) {
                    segment s = {Points[j], Points[(j+1)%Points.size()]};
                    if (ray_intersect_segment(s, ray))
                        num_intersections++;
                }
                if (num_intersections %2 == 1)
                    success++;
            }
            if (success >= 2) cout << "in" << endl;
            else cout << "out" << endl;


        }




    }
}
