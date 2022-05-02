#include <iostream>
#include <algorithm>
#include <bitset>
#include <unordered_map>
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
typedef vector<int> vi;
typedef pair<int, int> pii;


/*
 *                  Nikola problem
 *
 * row of N squares 1-N
 * initially at square 1, first jump to square 2.
 * - forward direction it must be one more square jump.
 * - backward direction is must be exactly the length.
 * - each square have fee,
 *
*/


int N;

ll Nikola(int  location, int last_jump, vector<int> & fee, vector<vector<ll>> &mat) {
    if (location == fee.size() - 1) return fee[location];

    if (location < 0 || location > fee.size()-1) return 501*N;
    if (mat[last_jump][location] < 501*N) return mat[last_jump][location];
    ll a = Nikola(location + last_jump + 1, last_jump + 1, fee, mat);
    if (last_jump == 0) return a + fee[location];
    ll b = Nikola(location - last_jump, last_jump, fee, mat);
    mat[last_jump][location] = min(a,b) + fee[location];
    return min(a,b) + fee[location];
}


int main() {
    cin >> N;
    vector<int> cost(N, 0);
    vector<vector<ll>> mat;
    mat.resize(N + 1, vector<ll>(N + 1, 501*N));
    for (int i = 0; i < N; ++i) {
        cin >> cost[i];
    }
    cout << (Nikola(0, 0, cost, mat) - cost[0]) << endl;
    return 0;
}