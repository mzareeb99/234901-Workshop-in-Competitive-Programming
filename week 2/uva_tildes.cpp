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
#include <string>
#include <vector>
#include <numeric>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vi;
typedef pair<int, int> pii;



int Num[1000000];

struct unionfind
{
    vector<int> rank;
    vector<int> parent;
    unionfind(int size)
    {
        rank=vector<int>(size,0);
        parent=vector<int>(size);
        for(int i=0;i<size;i++){
            parent[i]=i;
            Num[i]=1;
        }
    }

    int find(int x){
        int tmp=x;
        while(x!=parent[x]) x=parent[x];
        while(tmp!=x)//for log*, not needed most of the time
        {
            int remember=parent[tmp];
            parent[tmp]=x;
            tmp=remember;
        }
        return x;
    }

    void Union(int p, int q){
        p = find(p);
        q = find(q);
        if(q==p)
        {
            //alredy in the same group
            return;
        }

        if(rank[p] < rank[q]){ parent[p] = q; Num[q]+=Num[p]; }
        else {parent[q] = p; Num[p]+=Num[q];}
        if(rank[p] == rank[q]) rank[p]++;
    }

    int getRank(int x){
        return Num[find(x)];
    }
};
int main() {
    int q,n;
    cin >> n>>q;
    char l;

    unionfind uf(n+1);

    while(q--){
     cin >>l;
        int x,y;
        cin >>x;
    if(l=='t'){
        cin >>y;
        uf.Union(x,y);
    }else{
        cout<<uf.getRank(x)<<endl;
    }
    }
}