#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
#include <iomanip>      // std::setprecision
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<vector<int>> vvi;
typedef pair<int, int> ii;
typedef vector<pair<int, int>> vii;
typedef vector<vector<pair<int, int>>> vvii;

#define EPS 1e-9
#define MAX_SIZE 100

using namespace std;

#define INF 1e9
#define EPS 1e-9
#define PI                                                                     \
  acos(-1.0) // important constant; alternative #define PI (2.0 * acos(0.0))

double DEG_to_RAD(double d) { return d * PI / 180.0; }

double RAD_to_DEG(double r) { return r * 180.0 / PI; }

struct point {
    double x, y;        // only used if more precision is needed
    point() { x = y = 0.0; } // default constructor
    point(double _x, double _y) : x(_x), y(_y) {} // user-defined
    bool operator<(point other) const { // override less than operator
        if (fabs(x - other.x) > EPS)      // useful for sorting
            return x < other.x;             // first criteria , by x-coordinate
        return y < other.y;
    } // second criteria, by y-coordinate
    // use EPS (1e-9) when testing equality of two floating points
    bool operator==(point other) const {
        return (fabs(x - other.x) < EPS && (fabs(y - other.y) < EPS));
    }
};
//

double dist(point p1, point p2) {                // Euclidean distance
    // hypot(dx, dy) returns sqrt(dx * dx + dy * dy)
    return hypot(p1.x - p2.x, p1.y - p2.y); }           // return double

// rotate p by theta degrees CCW w.r.t origin (0, 0)
point rotate(point p, double theta) {
    double rad = DEG_to_RAD(theta);    // multiply theta with PI / 180.0
    return point(p.x * cos(rad) - p.y * sin(rad),
                 p.x * sin(rad) + p.y * cos(rad)); }

struct line { double a, b, c; };          // a way to represent a line

// the answer is stored in the third parameter (pass by reference)
void pointsToLine(point p1, point p2, line &l) {
    if (fabs(p1.x - p2.x) < EPS) {              // vertical line is fine
        l.a = 1.0;   l.b = 0.0;   l.c = -p1.x;           // default values
    } else {
        l.a = -(double)(p1.y - p2.y) / (p1.x - p2.x);
        l.b = 1.0;              // IMPORTANT: we fix the value of b to 1.0
        l.c = -(double)(l.a * p1.x) - p1.y;
    } }

// not needed since we will use the more robust form: ax + by + c = 0 (see above)
struct line2 { double m, c; };      // another way to represent a line

int pointsToLine2(point p1, point p2, line2 &l) {
    if (abs(p1.x - p2.x) < EPS) {          // special case: vertical line
        l.m = INF;                    // l contains m = INF and c = x_value
        l.c = p1.x;                  // to denote vertical line x = x_value
        return 0;   // we need this return variable to differentiate result
    }
    else {
        l.m = (double)(p1.y - p2.y) / (p1.x - p2.x);
        l.c = p1.y - l.m * p1.x;
        return 1;     // l contains m and c of the line equation y = mx + c
    } }

bool areParallel(line l1, line l2) {       // check coefficients a & b
    return (fabs(l1.a-l2.a) < EPS) && (fabs(l1.b-l2.b) < EPS); }

bool areSame(line l1, line l2) {           // also check coefficient c
    return areParallel(l1 ,l2) && (fabs(l1.c - l2.c) < EPS); }

// returns true (+ interSec point) if two lines are intersect
bool areIntersect(line l1, line l2, point &p) {
    if (areParallel(l1, l2)) return false;            // no interSec
    // solve system of 2 linear algebraic equations with 2 unknowns
    p.x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b);
    // special case: test for vertical line to avoid division by zero
    if (fabs(l1.b) > EPS) p.y = -(l1.a * p.x + l1.c);
    else                  p.y = -(l2.a * p.x + l2.c);
    return true; }

struct vec { double x, y;  // name: `vec' is different from STL vector
    vec(double _x, double _y) : x(_x), y(_y) {} };

vec toVec(point a, point b) {       // convert 2 points to vector a->b
    return vec(b.x - a.x, b.y - a.y); }

vec scale(vec v, double s) {        // nonnegative s = [<1 .. 1 .. >1]
    return vec(v.x * s, v.y * s); }               // shorter.same.longer

point translate(point p, vec v) {        // translate p according to v
    return point(p.x + v.x , p.y + v.y); }

// convert point and gradient/slope to line
void pointSlopeToLine(point p, double m, line &l) {
    l.a = -m;                                               // always -m
    l.b = 1;                                                 // always 1
    l.c = -((l.a * p.x) + (l.b * p.y)); }                // compute this

void closestPoint(line l, point p, point &ans) {
    line perpendicular;         // perpendicular to l and pass through p
    if (fabs(l.b) < EPS) {              // special case 1: vertical line
        ans.x = -(l.c);   ans.y = p.y;      return; }

    if (fabs(l.a) < EPS) {            // special case 2: horizontal line
        ans.x = p.x;      ans.y = -(l.c);   return; }

    pointSlopeToLine(p, 1 / l.a, perpendicular);          // normal line
    // intersect line l with this perpendicular line
    // the interSec point is the closest point
    areIntersect(l, perpendicular, ans); }

// returns the reflection of point on a line
void reflectionPoint(line l, point p, point &ans) {
    point b;
    closestPoint(l, p, b);                     // similar to distToLine
    vec v = toVec(p, b);                             // create a vector
    ans = translate(translate(p, v), v); }         // translate p twice

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
bool ccw(point p, point q, point r) {
    return cross(toVec(p, q), toVec(p, r)) > 0; }

// returns true if point r is on the same line as the line pq
bool collinear(point p, point q, point r) {
    return fabs(cross(toVec(p, q), toVec(p, r))) < EPS; }



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
    for (int i=0; i<Points.size(); i++) {
        Points[i].x = -Points[i].x;
        Points[i].y = -Points[i].y;
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
typedef pair<point, point> segment;


double area(segment seg) {
    return ((seg.first.y + seg.second.y) * (seg.second.x - seg.first.x)) / 2;
}
double y(segment seg, float f) {
    double x1 = seg.first.x, y1 = seg.first.y, x2 = seg.second.x, y2 = seg.second.y;
    double m = (y2 - y1) / (x2 - x1);
    double n = y1 - m * x1;
    return m * f + n;
}
point interSec(segment A, segment B) {
    double a1 = A.second.y - A.first.y;
    double b1 = A.first.x - A.second.x;
    double c1 = a1 * (A.first.x) + b1 * (A.first.y);
    double a2 = B.second.y - B.first.y;
    double b2 = B.first.x - B.second.x;
    double c2 = a2 * (B.first.x) + b2 * (B.first.y);
    double determinant = a1 * b2 - a2 * b1;
    if (determinant == 0) return { 10000, 10000 };
    else return { (b2 * c1 - b1 * c2) / determinant ,(a1 * c2 - a2 * c1) / determinant };
}
segment curr;
vector<segment> segments;
double visible(){
        double _area;
        double new_area = 0;
        double curr_area = area(curr);
        segment new_seg;
        vector<segment>  segments_curr;
        bool flag = false;
        for (auto seg : segments)
        {
            if (seg.second.x <= curr.first.x || curr.second.x <= seg.first.x) segments_curr.push_back(seg);
            else if (curr.first.x <= seg.first.x && curr.second.x <= seg.second.x) {
                new_seg = { curr.first , {seg.first.x, y(curr, seg.first.x)} };
                new_area += area(new_seg);
                segments_curr.push_back(new_seg);
                curr = {new_seg.second, curr.second};
                if (curr.first.y <= seg.first.y && curr.second.y <= y(seg, curr.second.x)) {
                    segments_curr.push_back(seg);
                }
                else if (curr.first.y >= seg.first.y && curr.second.y >= y(seg, curr.second.x)) {
                    segments_curr.push_back(curr);
                    segments_curr.push_back({{curr.second.x, y(seg, curr.second.x)}, seg.second });
                    new_area += (area(curr)) - (area({ seg.first, {curr.second.x, y(seg, curr.second.x)} }));
                }else {
                    point inter = interSec(curr, seg);
                    if (curr.first.y > seg.first.y) {
                        new_seg = {curr.first, inter};
                        new_area += area(new_seg) - area({seg.first, inter});
                        segments_curr.push_back(new_seg);
                        segments_curr.push_back({inter, seg.second});
                    }else {
                        segments_curr.push_back({seg.first, inter});
                        new_seg = {inter, curr.second};
                        new_area += area(new_seg) - area({ inter, {curr.second.x, y(seg, curr.second.x)} });
                        segments_curr.push_back(new_seg);
                        segments_curr.push_back({{curr.second.x, y(seg, curr.second.x)}, seg.second});
                    }
                }
                flag = true;
            }else if (curr.first.x >= seg.first.x && curr.second.x <= seg.second.x) {
                new_seg = { seg.first, {curr.first.x, y(seg, curr.first.x)} };
                segments_curr.push_back(new_seg);

                seg = {new_seg.second, seg.second};
                if (curr.first.y <= seg.first.y && curr.second.y <= y(seg, curr.second.x)) {
                    segments_curr.push_back(seg);
                }
                else if (curr.first.y >= seg.first.y && curr.second.y >= y(seg, curr.second.x)) {
                    segments_curr.push_back(curr);
                    segments_curr.push_back({{curr.second.x, y(seg, curr.second.x)}, seg.second });
                    new_area += (area(curr)) - (area({ seg.first, {curr.second.x, y(seg, curr.second.x)} }));
                }
                else {
                    point inter = interSec(curr, seg);
                    if (curr.first.y > seg.first.y) {
                        new_seg = { curr.first, inter };
                        new_area += area(new_seg) - area({ seg.first, inter });
                        segments_curr.push_back(new_seg);
                        segments_curr.push_back({inter, seg.second });
                    }
                    else {
                        segments_curr.push_back({seg.first, inter });
                        new_seg = { inter, curr.second };
                        new_area += area(new_seg) - area({ inter, {curr.second.x, y(seg, curr.second.x)} });
                        segments_curr.push_back(new_seg);
                        segments_curr.push_back({{curr.second.x, y(seg, curr.second.x)}, seg.second });
                    }
                }
                flag = true;
            }else if (curr.first.x >= seg.first.x && curr.second.x >= seg.second.x) {
                new_seg = { seg.first , {curr.first.x, y(seg, curr.first.x)} };
                segments_curr.push_back(new_seg);
                seg = { {curr.first.x, y(seg, curr.first.x)}, seg.second };
                if (curr.first.y <= seg.first.y && y(curr, seg.second.x) <= seg.second.y) {
                    segments_curr.push_back(seg);
                }
                else if (curr.first.y >= seg.first.y && y(curr, seg.second.x) >= seg.second.y) {
                    new_seg = { curr.first, {seg.second.x, y(curr, seg.second.x)} };
                    segments_curr.push_back(new_seg);
                    new_area += (area(new_seg)) - (area(seg));
                }
                else {
                    point inter = interSec(curr, seg);
                    if (curr.first.y > seg.first.y) {
                        new_seg = { curr.first, inter };
                        new_area += area(new_seg) - area({ seg.first, inter });
                        segments_curr.push_back(new_seg);
                        segments_curr.push_back({inter, seg.second });
                    }
                    else {
                        segments_curr.push_back({seg.first, inter });
                        new_seg = { inter, {seg.second.x, y(curr,seg.second.x) } };
                        new_area += area(new_seg) - area({ inter, seg.second });
                        segments_curr.push_back(new_seg);
                    }
                }
                curr = { {seg.second.x, y(curr, seg.second.x)}, curr.second };
            }else if (curr.first.x <= seg.first.x && curr.second.x >= seg.second.x) {
                new_seg = { curr.first, {seg.first.x, y(curr, seg.first.x)} };
                segments_curr.push_back(new_seg);
                new_area += area(new_seg);
                curr = { new_seg.second, curr.second };
                if (curr.first.y <= seg.first.y && y(curr, seg.second.x) <= seg.second.y) {
                    segments_curr.push_back(seg);
                }
                else if (curr.first.y >= seg.first.y && y(curr, seg.second.x) >= seg.second.y) {
                    new_seg = { curr.first, {seg.second.x, y(curr, seg.second.x)} };
                    segments_curr.push_back(new_seg);
                    new_area += (area(new_seg)) - (area(seg));
                }
                else {
                    point inter = interSec(curr, seg);
                    if (curr.first.y > seg.first.y) {
                        new_seg = { curr.first, inter };
                        new_area += area(new_seg) - area({ seg.first, inter });
                        segments_curr.push_back(new_seg);
                        segments_curr.push_back({inter, seg.second });
                    }
                    else {
                        segments_curr.push_back({seg.first, inter });
                        new_seg = { inter, {seg.second.x, y(curr,seg.second.x) } };
                        new_area += area(new_seg) - area({ inter, seg.second });
                        segments_curr.push_back(new_seg);
                    }
                }
                curr = { {seg.second.x, y(curr, seg.second.x)}, curr.second };
            }else{
                segments_curr.push_back(seg);
            }
        }
        if (!flag) {
            new_area += area(curr);
            segments_curr.push_back(curr);
        }
        segments = segments_curr;
        return new_area / curr_area;
}
int main() {
    int N;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        double x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        curr = { {x1, y1}, {x2, y2} };
        sort(segments.begin(), segments.end(), [](segment& a, segment& b){
            return a.first < b.first;
        });
        cout << fixed<<setprecision(8) << visible() << endl;
    }
    return 0;
}
