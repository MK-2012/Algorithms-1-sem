#include <iostream>
#include <deque>

using std::cin, std::cout, std::string, std::deque;

struct pair{
    long long num;
    long long val;
};

int main(){
    deque <long long> q1;
    deque <long long> q2;
    //std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    long long n = 0;
    long long k = 0;
    long long m = 0;
    long long temp;
    string s;
    cin >> n;
    for (long long i = 0; i < n; ++i) {
        cin >> s;
        switch(s[0]) {
            case '-':
                cout << q1.front() << '\n';
                q1.pop_front();
                --k;
                break;
            case '+':
                cin >> temp;
                q2.push_back(temp);
                ++m;
                break;
            case '*':
                cin >> temp;
                q2.push_front(temp);
                ++m;
                break;
        }
        if (k < m) {
            q1.push_back(q2.front());
            q2.pop_front();
            --m;
            ++k;
        }
    }
    return 0;
}
