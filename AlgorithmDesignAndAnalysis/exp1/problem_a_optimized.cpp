#include <iostream>
using namespace std;

const int MAX_SIZE = 100010;

int arr[MAX_SIZE];
int tmp[MAX_SIZE];
long long total = 0;

void mergeSort(int left, int right)
{
    if (right - left <= 1)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(left, mid);
    mergeSort(mid, right);

    int i = left, j = mid, k = left;
    // i=[left..mid-1], j=[mid..right-1]
    while (i < mid && j < right) {
        if (arr[i] <= arr[j]) {
            tmp[k++] = arr[i++];
        } else {
            tmp[k++] = arr[j++];
            total += mid - i; // arr[i..mid-1] > arr[j]
        }
    }
    while (i < mid)
        tmp[k++] = arr[i++];
    while (j < right)
        tmp[k++] = arr[j++];

    for (int t = left; t < right; t++)
        arr[t] = tmp[t];
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
        cin >> arr[i];

    mergeSort(0, n);

    cout << total << "\n";

    return 0;
}
