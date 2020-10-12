#include <iostream>
#include <vector>

using std::cin, std::cout, std::vector;

long long k = 0;

vector <long long> merge(vector <long long> &A, vector <long long> &B) {
    vector <long long> temp ={};
    long long l = 0;
    long long r = 0;
    while ((l < A.size()) && (r < B.size())){
        if (A[l] <= B[r]) {
            temp.push_back(A[l]);
            ++l;
        } else {
            temp.push_back(B[r]);
            ++r;
            k += A.size() - l;
        }
    }
    if (r == B.size()) {
        while (l < A.size()){
            temp.push_back(A[l]);
            ++l;
        }
    } else {
        while (r < B.size()) {
            temp.push_back(B[r]);
            ++r;
            k += A.size() - l;
        }
    }
    return temp;
}

void mergeSort(vector <long long> &A, long long l, long long r) {
    if (r - l <= 1)
        return;
    vector <long long> temp = {};
    long long med = (l + r) / 2;
    mergeSort(A, l, med);
    mergeSort(A, med, r);
    vector<long long> a, b;
    for (long long i = l; i < med; ++i)
        a.push_back(A[i]);
    for (long long i = med; i < r; ++i)
        b.push_back(A[i]);
    temp = merge(a, b);
    for (long long i = 0; i < r - l; ++i)
        A[i + l] = temp[i];
}

int main() {
    long long n = 0;
    vector <long long> AA = {};
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    freopen("inverse.in", "r", stdin);
    freopen("inverse.out", "w", stdout);
    cin >> n;
    for (long long i = 0; i < n; ++i) {
        long long tmp = 0;
        cin >> tmp;
        AA.push_back(tmp);
    }
    mergeSort(AA, 0, n);
    cout << k << '\n';
    return 0;
}
