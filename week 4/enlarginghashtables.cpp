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

int extended_euclid(int a, int b, int &x, int &y) {
    int xx = y = 0;
    int yy = x = 1;
    while (b) {
        int q = a / b;
        int t = b;
        b = a % b;
        a = t;
        t = xx;
        xx = x - q * xx;
        x = t;
        t = yy;
        yy = y - q * yy;
        y = t;
    }
    return a;
}






int isPrime(int x){
    if(x==2) return true;
    for(int i =2 ; i < sqrt(x)+1;i++) {
        if ((x%i) == 0) { return false ;}
    }
        return true;
}

int main() {


    int n;
    while(cin >>n){
        if(!n) break;
        ull c = 2*n;
        for(;;c++){
            if(isPrime(c)){
                cout << c;
                break;
            }
        }
        if(!isPrime(n)){
            cout << " (" << n ;
            cout << " is not prime)";
        }
        cout << endl;
    }


    return 0;
}