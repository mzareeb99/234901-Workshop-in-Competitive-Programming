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

int main() {
    int T;
    cin>>T;
    while(T--){
        int n;
        cin >>n;
        vector<string> names;
        while (n--){
            string s;
            cin>>s;
            names.push_back(s);
        }
        int sum = 0;
        for(int i =0 ; i< names.size();i++){
            int max = 0;
            for(int j = 0;j<names.size();j++){
                if(i==j) continue;
                int t = 0;
                while(names[i][t] ==names[j][t])
                    t++;
                max = t >max? t :max;
            }
            sum+=max+1;
        }
        cout<<sum<<endl;
    }

    return 0;
}