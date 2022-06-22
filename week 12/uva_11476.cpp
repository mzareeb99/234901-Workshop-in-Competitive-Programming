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
    if(n==1 || n==4)
        return false;
    if(n==2 || n==3)
        return true;
    ll m = n - 1;
    int r = 0;
    while (m%2 == 0){
        m >>= 1;
        r+=1;
    }
    /* !!! Deterministic version for n<2^64 !!! */
//    int dtrm_set[12] = {2,3,5,7,11,13,17,19,23,29,31,37};
//    for(ll a: dtrm_set){
//        if(a >= n) break;
    /* !!! End of deterministic version !!! */

    /* !!! Probablistic version !!! */
    while(k--){
        ll a = rand() % (n-4) + 2;
        /* !!! end of probablisitic version !!! */
        a = powmodn(a,m,n);
        if(a==1) continue;
        int i = r;
        while(i-- && a != n-1){
            a = mulmodn(a,a,n);
            if(a == 1) return false;
        }
        if(i == -1) return false;
    }
    return true;
}

ull getNextPrime(ull n){
    if (MR(n)){
        return n;
    }
    ll x = 0;
    do{
        x = pollard_rho(n);
    } while(!x);
    if (!MR(x)){
        return getNextPrime(x);
    }
    return x;
}

void updateNext(ull& n, map<ull, ull>& d){
    ull x = getNextPrime(n);

    ull k = 0;
    while (x * (n/x) == n){
        n /= x;
        ++k;
    }
    d[x] = k;
}

int main() {
    srand(time((NULL)));
    int T;
    cin >> T;
    while (T--){
        ull N;
        cin >> N;
        map<ull, ull> d;
        ull org_N = N;
        while (N > 1){
            updateNext(N, d);
        }
        cout << org_N << " = ";
        pair<ull, ull> last;
        ull counter = 1;
        for (auto p : d){
            if (counter == d.size()){
                last = p;
                break;
            }
            ++counter;
            if (p.second > 1){
                cout << p.first << "^" << p.second << " * ";
            } else{
                cout << p.first << " * ";
            }
        }
        if (last.second > 1){
            cout << last.first << "^" << last.second << endl;
        } else{
            cout << last.first << endl;
        }
    }
//    ll n = 100;
//    ll x = 0;
//    do{
//        x = pollard_rho(n);
//    } while(!x);
//    cout << pollard_rho(n) << endl;
    return 0;
}