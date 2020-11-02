#include <iostream>
#include <vector>

using std::cin, std::cout, std::vector;

template <typename T>
void swap(T &a, T &b) {
    T c = std::move(b);
    b = std::move(a);
    a = std::move(c);
}

int64_t partition(vector <int64_t>& arr, int64_t l, int64_t r) {
    int64_t j = r;
    int64_t i = l;
    int64_t m = arr[(r + l) / 2];
    while (true) {
        while (arr[i] < m) ++i;
        while (arr[j] > m) --j;
        if (i >= j) return j;
        swap(arr[i], arr[j]);
        --j;
        ++i;
    }
}

int64_t kStat(vector<int64_t>& arr, int64_t k) {
    int64_t l = 0;
    int64_t r = arr.size() - 1;
    while (true) {
        int64_t M = partition(arr, l, r);
        if (M == k) {
            int64_t max = 0;
            for (int64_t i = 0; i < M + 1; ++i) {
                if (arr[i] > max) {
                    max = arr[i];
                }
            }
            return max;
        } else if (k < M) {
            r = M;
        } else {
            l = M + 1;
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int64_t N, K = 0;
    cin >> N >> K;
    vector <int64_t> arr;
    for (int64_t i = 0; i < N; ++i) {
        int64_t tmp;
        cin >> tmp;
        arr.push_back(tmp);
    }
    int64_t res = kStat(arr, K);
    cout << res << '\n';
    return 0;
}
