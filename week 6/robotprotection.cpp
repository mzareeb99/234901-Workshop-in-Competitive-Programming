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
typedef vector<vll> vvll;
typedef vector<vull> vvull;
typedef pair<int, int> pii;
typedef pii ii;
typedef vector<pii> vii;
typedef priority_queue<int> max_iheap;
typedef priority_queue<ll> max_llheap;
typedef priority_queue<ull> max_ullheap;
typedef priority_queue<int, vi, greater<int>> min_iheap;
typedef priority_queue<int, vll, greater<ll>> min_llheap;
typedef priority_queue<int, vull, greater<ull>> min_ullheap;
typedef vector< vector<int> > vvi; // unweighted graph
typedef vector< vector< pair<int,int> > > vvii; // weighted graph
#define fastIO ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL)
#define print(x) cout<<x<<endl
#define eps 1e-9
#define INF 1e9


int dst(pair<int,int> &p1,pair<int,int>&p2,pair<int,int>&p3){
    return abs(sqrt((p2.first - p3.first)*(p2.first - p3.first) + (p2.second - p3.second)*(p2.second - p3.second)) -
            sqrt((p2.first - p1.first)*(p2.first - p1.first) + (p2.second - p1.second)*(p2.second - p1.second))) < 1e-5;
}


#define EPS 1e-9
#define MAX_SIZE 100

using namespace std;

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

// check p3 (leftmost) -> p2 -> p1 (rightmost) left turn (not right turn)
bool left(PT& p1, PT& p2, PT& p3)
{
    double cross = (p2.x - p3.x) * (p1.y - p3.y) - (p2.y - p3.y) * (p1.x - p3.x);

    if (fabs(cross) <= EPS)
        return true;    // to delete p2
    if (cross > 0)
        return true;
    return false;
}

int main() {

    vector<PT> Points;
    PT p;
    int n;
    //-------- read point set from file -------
    while(cin>>n && n!=0) {
        Points.clear();
        // cout << "open" << endl;
        while (n-- && cin >> p.x >> p.y) {
            Points.push_back(p);
        }

        //-------------- incremental alg. ---------
        // upper hull
        sort(Points.begin(), Points.end());
        stack<PT> stk_up;
        stk_up.push(Points[0]);
        stk_up.push(Points[1]);
        for (int i = 2; i < Points.size(); i++) {
            while ((stk_up.size() >= 2)) {
                PT p2, p3;
                p2 = stk_up.top();
                stk_up.pop();
                p3 = stk_up.top();
                if (!left(Points[i], p2, p3)) {
                    stk_up.push(p2);
                    break;
                }
            }
            stk_up.push(Points[i]);
        }
        // lower hull
        for (int i = 0; i < Points.size(); i++) {
            Points[i].x = -Points[i].x;
            Points[i].y = -Points[i].y;
        }
        sort(Points.begin(), Points.end());
        stack<PT> stk_low;
        stk_low.push(Points[0]);
        stk_low.push(Points[1]);
        for (int i = 2; i < Points.size(); i++) {
            while ((stk_low.size() >= 2)) {
                PT p2, p3;
                p2 = stk_low.top();
                stk_low.pop();
                p3 = stk_low.top();
                if (!left(Points[i], p2, p3)) {
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

        double sum = 0.0;
        for (int i = 0; i < CH.size() - 1; i++) {
            sum += 0.5 * (CH[i].x * CH[i + 1].y - CH[i + 1].x * CH[i].y);
            if (i == CH.size() - 2) {
                sum += 0.5 *(CH[i + 1].x * CH[0].y - CH[0].x * CH[i + 1].y);
            }
        }
        printf("%0.1f\n", sum);
//        reverse(CH.begin(), CH.end());  // ccw -> cw
//        for (vector<PT>::const_iterator iter = CH.begin(); iter != CH.end(); iter++)
//            cout << (*iter).x << ' ' << (*iter).y << endl;
//    }

    }
    return 0;
}
