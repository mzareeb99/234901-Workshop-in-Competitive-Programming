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
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<ull> vull;
typedef vector<bool> vb;
typedef vector<vi> v2i;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;
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

void solve(vvi& mat, int i, int j, vi& result, vii& items) {
    if(mat[i][j] == 0) {
        return;
    }
    if(mat[i - 1][j] == mat[i][j]) {
        solve(mat, i - 1, j, result, items);
    }
    else {
        solve(mat, i - 1, j - items[i].second, result, items);
        result.push_back(i-1);
    }
}
int main() {
    int items,size;
    while(cin >> size && cin >> items) {
        vvi mat(items+1, vector<int>(size+1, 0));
        vector<pair<int, int>> mat2;
        mat2.push_back({0, 0});
        for(int i = 0; i < items; i++) {
            pair<int, int> p;
            cin >> p.first >> p.second;
            mat2.push_back(p);
        }
        for(int i = 1; i < mat2.size(); i++) {
            for(int j = 1; j <= size; j++) {
                if (j < mat2[i].second) {
                    mat[i][j] = mat[i - 1][j];
                } else {
                    mat[i][j] = max(mat[i - 1][j - mat2[i].second] + mat2[i].first, mat[i - 1][j]);
                }
            }
        }
        vi result;
        solve(mat, items, size, result, mat2);
        cout << result.size() << endl;
        for(auto i : result) {
            cout << i << " ";
        }
        cout << endl;
    }
}