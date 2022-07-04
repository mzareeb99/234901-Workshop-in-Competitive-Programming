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
typedef pair<int, ii> iii;
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


ull step(ull n){
    ull res = 0;
    int d = 0;
    for (; n!=0; n/=10){
        d = n%10;
        res += d*d;
    }
    return res;
}


pair<ull, ull> getMuLambda(ull m){
    ull t = m;
    ull h = m;
    do{
        t = step(t);
        h = step(step(h));
    } while (t != h);

    h = m;
    ull mu = 0;
    while (t != h){
        ++mu;
        t = step(t);
        h = step(h);
    }

    ull lambda=0;
    t = h;
    do{
        ++lambda;
        h = step(h);
    } while (t != h);

    return {mu, lambda};
}


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


ll powmodn(ll a, ll q, ll n){
    ll res = 1;
    while(q){
        if (q & 1) res = mulmodn(res,a,n);
        a = mulmodn(a,a,n);
        q >>= 1;
    }
    return res;
}


bool MR(ll n, int k=5){
    if (n==2 || n==3){
        return true;
    }
    if (n<5){
        return false;
    }

    ull m = n-1;
    ull r = 0;
    while (m%2 == 0){
        m >>= 1;
        r += 1;
    }

    ull dtrm_set[12] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    for (ull a: dtrm_set){
        if (a >= n){
            break;
        }
        a = powmodn(a, m, n);
        if (a == 1){
            continue;
        }
        ll i = r;
        while (i-- && a != n - 1){
            a = (a*a) % n;
            if (a == 1){
                return false;
            }
        }
        if (i == -1){
            return false;
        }
    }
    return true;
}


int main(){
    fastIO;

    int P;
    cin >> P;
    while (P--){
        int K;
        ull m;
        cin >> K >> m;

        if (!MR(m)){
            cout << K << " " << m << " NO" << endl;
            continue;
        }

        auto p = getMuLambda(m);
        auto mu = p.first;
        auto lambda = p.second;

        if (lambda == 1){
            cout << K << " " << m << " YES" << endl;
        } else{
            cout << K << " " << m << " NO" << endl;
        }

    }

    return 0;
}
