#include <iostream>
using namespace std;

const int MAX_M = 30;
const int MAX_N = 30010;

// dp[i][j] = maximum v*p sum using the first i items with at most j money
int dp[MAX_M][MAX_N];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int N, m;
    cin >> N >> m;

    for (int i = 1; i <= m; i++) {
        int v, p;
        cin >> v >> p;

        for (int j = 0; j <= N; j++) {
            // Case 1: skip item i
            dp[i][j] = dp[i - 1][j];

            // Case 2: buy item i
            if (j >= v && dp[i - 1][j - v] + v * p > dp[i][j])
                dp[i][j] = dp[i - 1][j - v] + v * p;
        }
    }

    cout << dp[m][N] << "\n";

    return 0;
}
