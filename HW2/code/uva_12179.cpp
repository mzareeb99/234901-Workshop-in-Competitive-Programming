#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string.h>
#include <algorithm>
#include <queue>
#include <stack>
#include <iostream>

using namespace std;
int mat[128][128];
double memo[128][10005];
int main() {
    int testcase, cases = 1;
    int N, R, C;
    char tmp[128];
    cin>>testcase;
    while (testcase--) {
        memset(memo, 0, sizeof(memo));
        cin>>N>>R;
        for (int i = 0; i < N; i++) {
            cin>>tmp;
            for (int j = 0; j < N; j++) {
                mat[i][j] = tmp[j] == 'Y' ? 1 : 0x3f3f3f3f;
            }
        }
        for (int k = 0; k < N; k++) {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    mat[i][j] = min(mat[i][j], mat[i][k] + mat[k][j]);
                }
            }
        }
        memo[0][0] = 1;
        for (int i = 0; i <= N; i++) {
            for (int j = 0; j < 10005; j++) {
                if (memo[i][j] == 0)
                    continue;
                for (int k = 1; k <= R && j + k < 10005; k++) {
                    memo[i+1][j+k] += memo[i][j] / R;
                }
            }
        }
        cout<<"Case "<< cases++ << endl;
        cin>>C;
        int a,b,m;
        while (C--) {
            cin>>a>>b>>m;
            a--;
            b--;
            int dist = mat[a][b];
            double p = 0;
            if (dist == 0x3f3f3f3f) {
                p = 0;
            } else {
                for (int i = m; i >= 0; i--) {
                    p += memo[dist][i];
                }
            }
            printf("%.6lf\n", p);
        }
        puts("");
    }
    return 0;
}
