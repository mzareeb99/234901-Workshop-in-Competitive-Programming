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

vector<vector<int>> memo ;
string s="welcome to code jam";
string t;

int calc(int t1,int s1){
    if (s1==s.length())
        return 1;
    if (t1==t.length())
        return 0;
    if (memo[t1][s1]!=-1)
        return memo[t1][s1];
    int i=0;
    if(t[t1]==s[s1])
        i= calc(t1+1,s1+1);
    return memo[t1][s1]= (calc(t1+1,s1)+i)%10000;
}

int main() {
    int T;
    cin>>T;
    int test=1;
    getchar();
    while (T--){
        getline(cin,t);
        memo.assign(t.length(),vector<int>(s.length(),-1));
        cout<< "Case #"<<test<< ": ";
        cout<<setw(4)<< setfill('0')<< calc(0,0)<<endl;
        test++;
    }
    return 0;
}