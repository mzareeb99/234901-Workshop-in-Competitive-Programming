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
#include <iomanip>      // std::setprecision

using namespace std;
typedef long long ll;

int rec_calc (string& s , set<string>& sub_s , map<string,ll>& vals, map<string,ll>& tmp){
    ll sum=0;
    if (sub_s.find(s)!=sub_s.end()){
        sum+=vals[s];
        sum = sum % 1000000007;
    }
    for (int i=1 ; i <s.size(); i++){
        string t1,t2;
        t1=s.substr(0,i);
        if(sub_s.find(t1)==sub_s.end()) continue;
        ll right=0;
        ll left = vals[t1];
        t2=s.substr(i);
        if (tmp.find(t2)!= tmp.end())
            right=tmp[t2];
        else
            right= rec_calc(t2,sub_s,vals,tmp);
        sum+=(left*right);
        sum= sum% 1000000007;
    }
    tmp[s] = sum%1000000007;
    return sum%1000000007;
}

int main() {
    int num;
    string family;
    cin>>num>>family;
    map<string,ll> vals;
    set<string> sub_s;
    while (num--){
        string sub;
        ll val;
        cin>>sub>>val;
        sub_s.insert(sub);
        vals[sub]=val;
    }
    map<string,ll> tmp;
    cout<< rec_calc(family,sub_s,vals,tmp);
}