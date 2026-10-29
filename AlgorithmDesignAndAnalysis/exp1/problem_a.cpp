#include <iostream>
using namespace std;

const int MAX_SIZE = 100010;

int arr[MAX_SIZE];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
        cin >> arr[i];

    long long total = 0;

    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++)
            if (arr[i] > arr[j])
                total++;

    cout << total << "\n";

    return 0;
}
