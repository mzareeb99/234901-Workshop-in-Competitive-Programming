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


const long double pi=3.14159265358979323846;


int main() {
    // fastIO;
    int M, N;
    long double R;
    int ax, ay, bx, by;
    cin >> M >> N >> R;
    cin >> ax >> ay >> bx >> by;

    long double res = R * abs(ay-by);
    res += ((long double)(pi*min(ay, by)*abs(bx-ax)*R))/M;
    res /= N;
    // cout << res << endl;

    long double res2 = R * abs(ay-by);
    res2 /= N;
    res2 += 2*(R/N)*min(ay, by);
    printf("%Lf\n", min(res, res2));

    return 0;
}
