#include <iostream>
#include <algorithm>
using namespace std;

const int MAX_SIZE = 30010;

int price[MAX_SIZE];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int w, n;
    cin >> w >> n;

    for (int i = 0; i < n; i++)
        cin >> price[i];

    sort(price, price + n);

    int left = 0, right = n - 1, pairs = 0;
    while (left <= right) {
        if (left < right && price[left] + price[right] <= w) {
            left++;
            right--;
        } else { // left == right || price[left] + price[right] > w
            right--;
        }
        pairs++;
    }

    cout << pairs << "\n";

    return 0;
}
