#include <bits/stdc++.h>
#include <math.h>
using namespace std;
typedef long double d;
typedef vector<d> vld;
int main() {
    int N, s, L, W, n, l, r;
    while (cin >> N) {
        s = N / 2;
        d sp, x, ld, re, rd;
        cin >> L >> W;
        vector<int> p(N);
        for (int i = 0; i < N; i++)
            cin >> p[i];
        sp = d(L) / (s - 1);
        sort(p.begin(), p.end());
        vector<vld> dp(s + 1, vld(s + 1, 1e9));
        dp[0][0] = 0;
        for (l = 0; l <= s; l++)
            for (r = 0; r <= s; r++) {
                n = p[l + r - 1];
                ld = abs(n - (l - 1) * sp);
                x = n - (r - 1) * sp;
                rd = sqrt(x * x + W * W);
                if (l == 0) { if (r != 0) dp[l][r] = dp[l][r - 1] + rd; }
                else if (r == 0) dp[l][r] = dp[l - 1][r] + ld;
                else dp[l][r] = min(dp[l - 1][r] + ld, dp[l][r - 1] + rd);
            }
        printf("%.10Lf\n", dp[s][s]);
    }
    return 0;
}
