#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <map>

using namespace std;

typedef long long ll;
ll gcd(ll a, ll b){
    if(b==0)
    {
        return a;
    }
    return gcd(b, a%b);

}

ll mulmodn(ll a, ll b, ll n){
    ll res = 0;
    while(b){
        if(b & 1) res= (res+a) %n;
        a = (a*2)%n;
        b >>= 1;
    }
    return res;
}

ll f(ll a, ll c, ll n){
    return (mulmodn(a,a,n)+c)%n;
}

ll pollard_rho(ll n){
    if(n%2 == 0){
        return 2;
    }
    ll a = rand() % n;
    ll c = rand() % n;
    ll b = a;
    ll p;
    do{
        // a runs once
        a = f(a,c, n);
        // b runs twice as fast.
        b = f(f(b,c,n),c, n);
//        cout << a << " " << b << endl;
        p = gcd( abs(b-a) , n);
        if ( p > 1 && p != n)
            return p;
    } while (a!=b);

    return 0;

}


int main() {
    srand(time((NULL)));
    ll n = 15;
    ll x = 0;
    do{
        x = pollard_rho(n);
    } while(!x);
    cout << pollard_rho(n) << endl;
    return 0;
}