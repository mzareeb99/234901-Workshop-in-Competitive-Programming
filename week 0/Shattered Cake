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



int main(){
    ll Number;
    ll Width;

    while(cin>>Width) {
        cin >> Number;
        ll x, y;
        ll sum = 0;
        while (Number) {
            cin >> x >> y;
            sum += x * y;
            Number--;
        }
        double L = sum / Width;
        cout << L << endl;
    }
    return 0;
}