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


int main(){
   string s;
   int x;
   cin>>x;
   vector<string> vec;
    while (x) {
        cin >>s;
        vec.push_back(s);
        x--;
    }
   for(auto i : vec) {
       sort(i.begin(), i.end(),[](const char& lhs, const char& rhs){
           char first = tolower(lhs);
           char second = tolower(rhs);
           if(first < second){
               return true;
           }
           if(first == second){
               return lhs < rhs;
           }
           return false;
       });
       do {
           cout << i << endl;
       } while (next_permutation(i.begin(), i.end(),[](const char& lhs, const char& rhs){
           char first = tolower(lhs);
           char second = tolower(rhs);
           if(first < second){
               return true;
           }
           if(first == second){
               return lhs < rhs;
           }
           return false;
       }));
   }
    return 0;
}