#include <iostream>
#include <algorithm>
#include <bitset>
#include <unordered_map>
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
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef pair<int, int> pii;

int main(){
    int g;
    cin >>g;
    int t =1;
    while(g--){
        int m;
        cin >>m;
        vector<int> vec (100001);
        for(int i = 1; i <= m ; i++)
            cin>>vec[i];
        int k =0;
        for(int i = 1 ; i <=m ; i++){
            if(vec[i] - vec[i-1] > k)
                k = vec[i]-vec[i-1];
        }
        int sum = k;
        for(int i =1; i <=m;i++){
            if(vec[i]-vec[i-1] ==k)
                k--;
            else if(vec[i]-vec[i-1] > k){
                sum++;
                break;
            }
        }
        cout<<"Case "<<t++<<": "<<sum<<endl;

    }
    return 0;
}