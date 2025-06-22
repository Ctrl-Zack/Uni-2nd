#include <iostream>
#include <vector>
#include <stdint.h>

uint64_t merge(std::vector<uint32_t>& arr, uint32_t left, uint32_t mid, uint32_t right)
{
    uint64_t ans = 0;
    uint32_t n1 = mid - left + 1;
    uint32_t n2 = right - mid;

    std::vector<uint32_t> L(n1), R(n2);

    for (size_t i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (size_t j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    uint32_t i = 0, j = 0;
    uint32_t k = left;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++], ans += (n1 - i);
    }

    while (i < n1)
        arr[k++] = L[i++];

    while (j < n2)
        arr[k++] = R[j++];

    return ans;
}

void mergeSort(std::vector<uint32_t>& arr, uint32_t left, uint32_t right, uint64_t &ans)
{
    if (left >= right)
        return;

    int mid = left + ((right - left) >> 1);
    mergeSort(arr, left, mid, ans);
    mergeSort(arr, mid + 1, right, ans);
    ans += merge(arr, left, mid, right);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); std::cout.tie(nullptr);

    uint64_t ans = 0;
    uint32_t n;
    std::cin >> n;
    std::vector<uint32_t> arr(n);

    for (size_t i = 0; i < n; i++)
        std::cin >> arr[i];

    mergeSort(arr, 0, n - 1, ans);

    std::cout << ans;

    return 0;
}