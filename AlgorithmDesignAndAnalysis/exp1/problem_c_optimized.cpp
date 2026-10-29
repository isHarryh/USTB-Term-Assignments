#include <iostream>
using namespace std;

const int MAX_N = 30010;

// dp[j] = maximum v*p sum with at most j money, over the items read so far
int dp[MAX_N];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int N, m;
    cin >> N >> m;

    for (int i = 0; i < m; i++) {
        int v, p;
        cin >> v >> p;

        // j=[N..v]
        for (int j = N; j >= v; j--) {
            int tmp = dp[j - v] + v * p;
            if (tmp > dp[j])
                dp[j] = tmp;
        }
    }

    cout << dp[N] << "\n";

    return 0;
}
