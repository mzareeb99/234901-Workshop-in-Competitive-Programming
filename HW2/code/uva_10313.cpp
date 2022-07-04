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
#include <stack>
#include <vector>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vll> vvll;
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
#define MAX 305
template<class T>
void printVec(vector<T> &s){
    for(auto &i:s)
        cout<<i<<" ";
    cout<<endl;
}


int main() {
        vvll dp(MAX,vll(MAX,0));

        for (int j = 0; j <= 300; ++j)
             dp[0][j] = 1;

        for (int i=0;i<=300; ++i)
            for (int j=1;j<=300;++j) {
                dp[i][j] = dp[i][j - 1];
                if(i>=j)
                    dp[i][j] +=dp[i - j][j];
            }
        string str;
        while(getline(cin,str)&&!str.empty()){
            vi vec;
            string temp;
            for(auto i  :str){
                if(isdigit(i))
                    temp+=i;
                else{
                    if(!temp.empty()){
                        int a = stoi(temp);
                        vec.push_back(a);
                        temp="";
                    }
                }
            }
            if(!temp.empty()){
                int a = stoi(temp);
                vec.push_back(a);
            }

            int n = min(vec[0],300);
            if(n==0) cout<<"1"<<endl;
            else if(vec.size() ==1) cout<<dp[n][n]<<endl;
            else if(vec.size() ==2){
                int a= min (vec[1],300);
                cout<<dp[n][a]<<endl;
            }else{
                int a = vec[1];
                int b = vec[2];
                 cout<<dp[n][min(b,300)] - dp[n][min(300, max(0, a - 1))]<<endl;
            }
        }
    return 0;

}
