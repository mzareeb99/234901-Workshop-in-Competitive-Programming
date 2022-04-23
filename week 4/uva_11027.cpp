#ifndef CONCATENATE
#define CONCATENATE(s1, s2)     s1##s2
#define EXPAND_THEN_CONCATENATE(s1, s2) CONCATENATE(s1, s2)
#endif

#ifndef UNIQUE_IDENTIFIER
#ifdef __COUNTER__
#define UNIQUE_IDENTIFIER(prefix) EXPAND_THEN_CONCATENATE(prefix, __COUNTER__)
#else
#define UNIQUE_IDENTIFIER(prefix) EXPAND_THEN_CONCATENATE(prefix, __LINE__)
#endif /* COUNTER */
#else
#endif /* UNIQUE_IDENTIFIER */
#define static_block STATIC_BLOCK_IMPL1(UNIQUE_IDENTIFIER(_static_block_))

#define STATIC_BLOCK_IMPL1(prefix) \
	STATIC_BLOCK_IMPL2(CONCATENATE(prefix,_fn),CONCATENATE(prefix,_var))

#define STATIC_BLOCK_IMPL2(function_name,var_name) \
static void function_name(); \
static int var_name __attribute((unused)) = (function_name(), 0) ; \
static void function_name()

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

#define print(x) cout<<x<<endl

vector<ull> factorial(18);

static_block {
    factorial[0]= 1;
    for(int i = 1; i < 18; i++) factorial[i] =factorial[i-1]*i;
}

int main(){
    int T,K,tc = 1;
    cin >>T;
    while(T--){
        string s,s2;
        vi cont(26);
        cin>>s>>K;
        int L =s.length();
        for(int i = 0;i < L;++i)
            ++cont[s[i] - 'a'];
        int odd = 0,ind = -1;
        for(int i = 0;i < 26;++i)
            if(cont[i] & 1)
                ++odd, ind = i;
        cout<<"Case "<<tc++<<": ";

        if(odd <= 1){
            char mid;
            if(odd == 1) mid = 'a' + ind;
            for(int i = 0;i < 26;++i) cont[i] >>= 1;
            int sum = L / 2;
            ll total = factorial[sum];
            for(int i = 0;i < 26;++i){
                for(int j = 1;j <= cont[i];++j)
                    total /= j;
            }
            if(total < K) cout<<"XXX"<<endl;
            else{
                for(int i = 0;i < sum;++i){
                    for(int j = 0;j < 26;++j){
                        if(cont[j] != 0){
                            ll aux = factorial[sum - i - 1];
                            for(int k = 0;k < 26;++k){
                                for(int l = 1;l <= cont[k] - (k == j);++l)
                                    aux /= l;
                            }
                            if(K <= aux){
                                --cont[j];
                                s2[i] = 'a' + j;
                                break;
                            }else K -= aux;
                        }
                    }
                }
                for(int i = 0;i < L / 2;++i) cout<<s2[i];
                if(odd) cout<<mid;
                for(int i = 0;i < L / 2;++i) cout<<s2[L / 2 - 1 - i];
                cout<<endl;
            }
        }else cout<<"XXX"<<endl;
    }
    return 0;
}
