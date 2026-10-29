#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

const int MAX_LEN = 5005;
const int MOD = 100000000;

int fPrev[MAX_LEN], fCur[MAX_LEN];
int gPrev[MAX_LEN], gCur[MAX_LEN];

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

    for (int j = 0; j <= m; j++)
        gPrev[j] = 1;

    for (int i = 1; i <= n; i++) {
        fCur[0] = 0;
        gCur[0] = 1;

        for (int j = 1; j <= m; j++) {
            bool eq = (x[i - 1] == y[j - 1]);

            int best = fPrev[j] > fCur[j - 1] ? fPrev[j] : fCur[j - 1];
            if (eq && fPrev[j - 1] + 1 > best)
                best = fPrev[j - 1] + 1;
            fCur[j] = best;

            long long cnt = 0;
            if (fPrev[j] == best)
                cnt += gPrev[j];
            if (fCur[j - 1] == best)
                cnt += gCur[j - 1];
            if (eq && fPrev[j - 1] + 1 == best)
                cnt += gPrev[j - 1];
            if (fPrev[j - 1] == best)
                cnt -= gPrev[j - 1];

            cnt %= MOD;
            if (cnt < 0)
                cnt += MOD;
            gCur[j] = (int)cnt;
        }

        swap(fPrev, fCur);
        swap(gPrev, gCur);
    }

    cout << fPrev[m] << "\n" << gPrev[m] << "\n";

    return 0;
}
