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



ll gcd(int a, int b){ //greater common divider
    if(a < b) return gcd(b,a);
    if(b == 0) return a;
    return gcd(b,a%b);
}



ll lcm(int a, int b){//least common multiple
    return (a*b)/(gcd(a,b));
}



int main(){
    int T;
    cin >>T;
    while(T--){
        ll a,b;
        cin >>a>>b;
       if(!(b%a))
           cout<<a<<" "<<b<<endl;
       else
           cout<<"-1"<<endl;
    }
}