#include <iostream>
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
#include <vector>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pair<double,double>> vpd;
typedef pair<int,int> ii;
typedef pair<double,double> dd;
typedef vector<ii> vii;
typedef vector<vi> vvi;
typedef set<int> si;
typedef vector<si> vsi;
typedef vector< vector<int> > vvi; // unweighted graph
typedef vector< vector< pair<int,int> > > vvii; // weighted graph
using namespace std;
#include <iomanip>      // std::setprecision
#include <unordered_map>

int type1(string&s,string&l) {
    auto index = l.find(s);
    int ret =0;
    while(index !=-1){
            ret++;
        index = l.find(s,index+1);
    }
return ret;
}

int type2(string&s,string&l){
    //remove
    int ret =0;
    unordered_map<string,int> ht;
        for(int j =0 ; j <s.length();j++){
            string temp = s;
            temp = temp.substr(0,j) + temp.substr(j+1,s.length()-j);
            if(ht.find(temp) != ht.end() || temp.length() != s.length()-1) continue;
            ht[temp] =2;
            ret += type1(temp,l);
        }
    return ret;
}
int type3(string&s,string&l){
    //add
    vector<string> ch = {"A","G","C","T"};
    int ret =0;
    for(int i = 0 ;i<4;i++){
        unordered_map<string,int> ht;
        for(int j =0 ; j <=s.length();j++){
            string temp =s;
            temp.insert(j,ch[i]);
            if(ht.find(temp) != ht.end()) continue;
            ht[temp] =3;
            ret += type1(temp,l);
        }
    }
    return ret;
}



    void print(vi& i){
    for(auto &j:i)
        cout<<j<<" ";
    cout<<endl;
}


int main() {
    string S,L;
    while(cin>>S && S !="0"){
        cin >>L;
        vi ret(3,0);
        ret[0] = type1(S,L);
        ret[1] = type2(S,L);
        ret[2] = type3(S,L);
        print(ret);
    }

    return 0;

}
