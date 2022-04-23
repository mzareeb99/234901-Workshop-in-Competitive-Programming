#include <algorithm>
#include <cstdio>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <vector>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef pair<int, int> pii;
int main(){
   int test,x,size;
    scanf("%d",&test);
    while(test--){
        scanf("%d",&size);
        vector<int> arr;
        while(size--) {
            cin>>x;
            arr.push_back(x);
        }
            sort(arr.begin(),arr.end());
            int length = 0;
            for(int i =0 ;i< arr.size()-1;i++){
                if(arr[i+1] != arr[i])
                     length+=arr[i+1]-arr[i];
            }
            cout<<length*2<<endl;
        }
        return 0;
    }