#include <iostream>
#include <cstdlib>
#include <time.h>
#include <math.h>
#include <chrono>
#include <vector>
#include <bitset>
#include <stdio.h>
#include <fstream>
#include <stack>
#include <algorithm>
#include <set>

using namespace std;
typedef long long ll;
typedef pair<double,double> dd;
#define INF 1e9
#define EPS 1e-9
#define PI acos(-1.0) // important constant; alternative #define PI (2.0 * acos(0.0))

double DEG_to_RAD(double d) { return d * PI / 180.0; }

double RAD_to_DEG(double r) { return r * 180.0 / PI; }

// struct point_i { int x, y; };    // basic raw form, minimalist mode
struct point_i { int x, y;     // whenever possible, work with point_i
    point_i() { x = y = 0; }                      // default constructor
    point_i(int _x, int _y) : x(_x), y(_y) {} };         // user-defined

struct point {
    double x, y;   // only used if more precision is needed
    point() { x = y = 0.0; }                      // default constructor
    point(double _x, double _y) : x(_x), y(_y) {}        // user-defined
    virtual bool operator < (point other) const { // override less than operator
        if (fabs(x - other.x) > EPS)                 // useful for sorting
            return x < other.x;          // first criteria , by x-coordinate
        return y < other.y; }          // second criteria, by y-coordinate
    virtual // use EPS (1e-9) when testing equality of two floating points
    bool operator == (point other) const {
        return (fabs(x - other.x) < EPS && (fabs(y - other.y) < EPS)); } };

double dist(point p1, point p2) {                // Euclidean distance
    // hypot(dx, dy) returns sqrt(dx * dx + dy * dy)
    return hypot(p1.x - p2.x, p1.y - p2.y); }           // return double

// rotate p by theta degrees CCW w.r.t origin (0, 0)
point rotate(point p, double theta) {
    double rad = DEG_to_RAD(theta);    // multiply theta with PI / 180.0
    return point(p.x * cos(rad) - p.y * sin(rad),
                 p.x * sin(rad) + p.y * cos(rad)); }

struct vec { double x, y;  // name: `vec' is different from STL vector
    vec(double _x, double _y) : x(_x), y(_y) {} };

vec toVec(point a, point b) {       // convert 2 points to vector a->b
    return vec(b.x - a.x, b.y - a.y); }

vec scale(vec v, double s) {        // nonnegative s = [<1 .. 1 .. >1]
    return vec(v.x * s, v.y * s); }               // shorter.same.longer

point translate(point p, vec v) {        // translate p according to v
    return point(p.x + v.x , p.y + v.y); }

// convert point and gradient/slope to line
            // compute this

double dot(vec a, vec b) { return (a.x * b.x + a.y * b.y); }

double norm_sq(vec v) { return v.x * v.x + v.y * v.y; }

// returns the distance from p to the line defined by
// two points a and b (a and b must be different)
// the closest point is stored in the 4th parameter (byref)
double distToLine(point p, point a, point b, point &c) {
    // formula: c = a + u * ab
    vec ap = toVec(a, p), ab = toVec(a, b);
    double u = dot(ap, ab) / norm_sq(ab);
    c = translate(a, scale(ab, u));                  // translate a to c
    return dist(p, c); }           // Euclidean distance between p and c

// returns the distance from p to the line segment ab defined by
// two points a and b (still OK if a == b)
// the closest point is stored in the 4th parameter (byref)
double distToLineSegment(point p, point a, point b, point &c) {
    vec ap = toVec(a, p), ab = toVec(a, b);
    double u = dot(ap, ab) / norm_sq(ab);
    if (u < 0.0) { c = point(a.x, a.y);                   // closer to a
        return dist(p, a); }         // Euclidean distance between p and a
    if (u > 1.0) { c = point(b.x, b.y);                   // closer to b
        return dist(p, b); }         // Euclidean distance between p and b
    return distToLine(p, a, b, c); }          // run distToLine as above

double angle(point a, point o, point b) {  // returns angle aob in rad
    vec oa = toVec(o, a), ob = toVec(o, b);
    return acos(dot(oa, ob) / sqrt(norm_sq(oa) * norm_sq(ob))); }

double cross(vec a, vec b) { return a.x * b.y - a.y * b.x; }

//// another variant
//int area2(point p, point q, point r) { // returns 'twice' the area of this triangle A-B-c
//  return p.x * q.y - p.y * q.x +
//         q.x * r.y - q.y * r.x +
//         r.x * p.y - r.y * p.x;
//}

// note: to accept collinear points, we have to change the `> 0'
// returns true if point r is on the left side of line pq
bool ccw(const point& p, point q, point r) {
    return 0 < cross(toVec(p, std::move(q)), toVec(p, r)); }

// returns true if point r is on the same line as the line pq
bool collinear(const point& p, point q, point r) {
    return fabs(cross(toVec(std::move(q), p), toVec(p, std::move(r)))) < EPS; }



vector<point> convex_hull(vector<point> Points) {

    //-------------- incremental alg. ---------
    // upper hull
    sort(Points.begin(), Points.end());
    stack<point> stk_up;
    stk_up.push(Points[0]);
    stk_up.push(Points[1]);
    for (int i=2; i<Points.size(); i++) {
        while ((stk_up.size() >= 2)) {
            point p2, p3;
            p2 = stk_up.top();
            stk_up.pop();
            p3 = stk_up.top();
            if (ccw(Points[i], p2, p3)){
                stk_up.push(p2);
                break;
            }
        }
        stk_up.push(Points[i]);
    }
    // lower hull
    for (auto & Point : Points) {
        Point.x = -Point.x;
        Point.y = -Point.y;
    }
    sort(Points.begin(), Points.end());
    stack<point> stk_low;
    stk_low.push(Points[0]);
    stk_low.push(Points[1]);
    for (int i=2; i<Points.size(); i++) {
        while ((stk_low.size() >= 2)) {
            point p2, p3;
            p2 = stk_low.top();
            stk_low.pop();
            p3 = stk_low.top();
            if (ccw(Points[i], p2, p3)){
                stk_low.push(p2);
                break;
            }
        }
        stk_low.push(Points[i]);
    }

    // print convex hull - cw order from leftmost point
    vector<point> CH;
    stk_low.pop();
    point p;
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

struct point_x :public point{
    double x,y;
    point_x(double _x, double _y) :  x(_x),y(_y){}        // user-defined
    bool operator < (const point_x& other) const  { // override less than operator
        if (fabs(x - other.x) > EPS)                 // useful for sorting
            return x < other.x;          // first criteria , by x-coordinate
        return y < other.y; }          // second criteria, by y-coordinate
    // use EPS (1e-9) when testing equality of two floating points
    bool operator == (const point_x& other) const  {
        return (fabs(x - other.x) < EPS && (fabs(y - other.y) < EPS)); } };


struct point_y{
    double x;
    double y;
    point_y(double _x, double _y) : x(_x), y(_y) {}
    bool operator<(const point_y& p) const {
        if (y == p.y) return x < p.x;
        return y < p.y;
    }
    bool operator==(const point_y& p) const {
        return x == p.x && y == p.y;
    } };


int main() {
    int n;
    while (cin >> n && n != 0) {
        vector<point_x> points;
        while (n--) {
            double x, y;
            cin >> x >> y;
            points.emplace_back(x, y);
        }
        sort(points.begin(), points.end());
        pair<dd,dd> closest_points = {{points[0].x, points[0].y}, {points[1].x, points[1].y}};
        set<point_y> strip;
        double min_dist = INF;
        for (auto & curr_point : points) {
            point_y curr_point_y = point_y(curr_point.x, curr_point.y);
            set<point_y> to_remove;
            for (auto& it : strip) 
                if (curr_point_y.x - it.x >= min_dist) 
                    to_remove.insert(it);
            for (auto& it : to_remove)
                strip.erase(it);
            auto low_bound = strip.lower_bound(point_y(0, curr_point.y - min_dist));
            auto up_bound = strip.upper_bound(point_y(0, curr_point.y + min_dist));
            curr_point_y = point_y(curr_point.x, curr_point.y);
            while (low_bound != up_bound) {
                point_y cand = *low_bound;
                double curr_dist = hypot(cand.x - curr_point_y.x, cand.y - curr_point_y.y);
                if (curr_dist < min_dist) {
                    min_dist = curr_dist;
                    closest_points = {{cand.x, cand.y}, {curr_point_y.x, curr_point_y.y}};
                }
                low_bound++;
            }
            strip.insert(point_y(curr_point.x, curr_point.y));
        }
        pair<dd,dd>closes={closest_points.first, closest_points.second};
        printf("%0.2f %0.2f %0.2f %0.2f\n", closes.first.first, closes.first.second, closes.second.first, closes.second.second);

    }

    return 0;
}
