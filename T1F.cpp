#include <iostream>
#include <vector>
#define ll long long

using std::cin, std::cout, std::vector;

ll k = 0;

vector <ll> merge(vector <ll> &A, vector <ll> &B) {
    vector <ll> temp ={};
    ll l = 0;
    ll r = 0;
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

void m_s(vector <ll> &A, ll l, ll r) {
    if (r - l <= 1)
        return;
    vector <ll> temp = {};
    ll med = (l + r) / 2;
    m_s(A, l, med);
    m_s(A, med, r);
    vector<ll> a, b;
    for (ll i = l; i < med; ++i)
        a.push_back(A[i]);
    for (ll i = med; i < r; ++i)
        b.push_back(A[i]);
    temp = merge(a, b);
    for (ll i = 0; i < r - l; ++i)
        A[i + l] = temp[i];
}

int main() {
    ll n = 0;
    vector <ll> AA = {};
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    freopen("inverse.in", "r", stdin);
    freopen("inverse.out", "w", stdout);
    cin >> n;
    for (ll i = 0; i < n; ++i) {
        ll tmp = 0;
        cin >> tmp;
        AA.push_back(tmp);
    }
    m_s(AA, 0, n);
    cout << k << '\n';
    return 0;
}
