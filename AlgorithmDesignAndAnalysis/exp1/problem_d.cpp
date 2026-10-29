#include <iostream>
#include <string>
using namespace std;

const int MAX_LEN = 5005;
const int MOD = 100000000;

// f[i][j] = LCS length of x[0..i-1] and y[0..j-1]
// g[i][j] = number of alignments that reach that length

int f[MAX_LEN][MAX_LEN];
int g[MAX_LEN][MAX_LEN];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    string x, y;
    char c;

    while (cin >> c && c != '.')
        x += c;
    while (cin >> c && c != '.')
        y += c;

    int n = x.size(), m = y.size();

    for (int i = 0; i <= n; i++)
        g[i][0] = 1;
    for (int j = 0; j <= m; j++)
        g[0][j] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            bool eq = (x[i - 1] == y[j - 1]);

            int best = f[i - 1][j] > f[i][j - 1] ? f[i - 1][j] : f[i][j - 1];
            if (eq && f[i - 1][j - 1] + 1 > best)
                best = f[i - 1][j - 1] + 1;
            f[i][j] = best;

            long long cnt = 0;
            if (f[i - 1][j] == best)
                cnt += g[i - 1][j];
            if (f[i][j - 1] == best)
                cnt += g[i][j - 1];
            if (eq && f[i - 1][j - 1] + 1 == best)
                cnt += g[i - 1][j - 1];

            if (f[i - 1][j - 1] == best)
                cnt -= g[i - 1][j - 1];

            cnt %= MOD;
            if (cnt < 0)
                cnt += MOD;
            g[i][j] = (int)cnt;
        }
    }

    cout << f[n][m] << "\n" << g[n][m] << "\n";

    return 0;
}
