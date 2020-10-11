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
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    long long requests = 0;
    long long queue_amount = 0;
    long long buffer = 0;
    long long temp;
    string s;
    cin >> requests;
    for (long long i = 0; i < requests; ++i) {
        cin >> s;
        switch(s[0]) {
            case '-':
                cout << q1.front() << '\n';
                q1.pop_front();
                --queue_amount;
                break;
            case '+':
                cin >> temp;
                q2.push_back(temp);
                ++buffer;
                break;
            case '*':
                cin >> temp;
                q2.push_front(temp);
                ++buffer;
                break;
        }
        if (queue_amount < buffer) {
            q1.push_back(q2.front());
            q2.pop_front();
            --buffer;
            ++queue_amount;
        }
    }
    return 0;
}
