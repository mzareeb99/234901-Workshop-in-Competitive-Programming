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


string tolowerS(string s){
    string t="";
    for(auto &i:s){
        t+=tolower(i);
    }
    sort(t.begin(),t.end());
    return t;
}

int main(){

    vector<string> si;
    string in;
    while(cin>>in){
        if(in == "#") break;
        si.push_back(in);
    }
    vector<pair<string,int>> temp;
    int j = 0 ;
    for(const auto& i : si){
        temp.emplace_back(tolowerS(i),j);
        j++;
    }

    sort(temp.begin(),temp.end());
    for(int i = 0 ; i < temp.size()-1;i++){
        bool del = false;
        if(!temp[i].first.empty())
        for(int k= i+1 ; k < temp.size(); k++)
        if(temp[i].first == temp[k].first) {
            // temp.erase(temp.begin(),temp.end(),)
            temp[k].first = " ";
            del = true;
        }
        if(del)
            temp[i].first = " ";
    }

    vector<string> ret;
    for(const auto& i : temp){
        if(i.first != " ")
            ret.push_back(si[i.second]);
            //cout<<si[i.second]<<endl;
    }
    sort(ret.begin(),ret.end());
    for(const auto& i : ret){
            cout<<i<<endl;
    }

    return 0;
}