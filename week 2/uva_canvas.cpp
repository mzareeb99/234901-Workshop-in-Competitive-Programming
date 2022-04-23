
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
typedef pair<int, int> pii;


int main() {
    ull tests;
    cin >> tests;
    while(tests--) {
        priority_queue<ull, vector<ull>, greater<ull>> heap;
        int nums;
        cin >> nums;

        for (int i = 0; i < nums; i++) {
            ull x;
            cin >> x;
            heap.push(x);
        }

        ull cost = 0;
        while (heap.size()>=2) {
            ull tmp = heap.top();
            heap.pop();
            tmp += heap.top();
            heap.pop();
            cost += tmp;
            if (!heap.empty()) {
                heap.push(tmp);
            }
        }
        cout << cost << endl;

    }

    return 0;
}