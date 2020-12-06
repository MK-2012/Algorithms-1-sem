#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <string>

using std::set, std::map, std::cout, std::cin, std::vector, std::string;

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int64_t N, M, K;
    cin >> N >> M >> K;
    std::map <int64_t, set<int64_t>> dict;
    vector <set<int64_t>> sets(100001);
    string str;
    for (int64_t i = 0; i < K; ++i) {
        cin >> str;
        switch(str[0]) {
            case 'A': {
                int64_t s, e;
                cin >> e >> s;
                sets[s].insert(e);
                dict[e].insert(s);
                break;
            }
            case 'D': {
                int64_t s, e;
                cin >> e >> s;
                sets[s].erase(e);
                dict[e].erase(s);
                break;
            }
            case 'C': {
                int64_t s;
                cin >> s;
                for (auto j = sets[s].begin(); j != sets[s].end(); ++j) {
                    dict[*j].erase(s);
                }
                sets[s].clear();
                break;
            }
            case 'L': {
                if (str.length() == 7) {
                    int64_t s;
                    cin >> s;
                    if (!sets[s].empty()) {
                        for (auto j = sets[s].begin(); j != sets[s].end(); ++j) {
                            cout << *j << " ";
                        }
                        cout << '\n';
                    } else {
                        cout << "-1\n";
                    }
                } else {
                    int64_t e;
                    cin >> e;
                    if (!dict[e].empty()) {
                        for (auto j = dict[e].begin(); j != dict[e].end(); ++j) {
                            cout << *j << " ";
                        }
                        cout << '\n';
                    } else {
                        cout << "-1\n";
                    }
                }
                break;
            }
        }
    }
    return 0;
}