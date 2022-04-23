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
typedef vector<int> vi;
typedef pair<int, int> pii;

bool is_palindrom (string x){
    int j=5;
    for (int i=0; i<3 ; i++){
        if (x[i]!=x[j])
            return false;
        j--;
    }
    return true ;
}

int main() {
    int num;
    cin>>num ;
    set<int> palindrome ;
    for(int i=100000 ; i<1000000 ; i++){
        string s = to_string(i);
        if (is_palindrom(s))
            palindrome.insert(i);
    }
    while (num--){
        int s;
        cin >> s ;
        auto it = palindrome.lower_bound(s);
        int max = *it;
        int min = 0;
        if (it != palindrome.begin()) {
            --it;
            min = *it;
        }
        int x = (max-s) >= (s-min)? min : max ;
        cout << x << endl ;
    }
}