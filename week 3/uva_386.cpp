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



    for(int i=2 ; i <= 200;i++){
        for(int j = 2 ; j <= 200;j++) {
            if(j < i)
            for (int k = 2; k <= 200; k++) {
                if(j <= k)
                for (int m = 2; m <= 200; m++) {
                    if(j <=m && k<=m)
                        if(i*i*i == j*j*j + m*m*m + k*k*k){
                            printf("Cube = %d, Triple = (%d,%d,%d)\n",i,j,k,m);
                        }
                }
            }
        }


    }

    return 0;
}