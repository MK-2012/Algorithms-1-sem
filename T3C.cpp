#include <iostream>
#include <algorithm>

using std::cin, std::cout;

class DerOtr {
private:
    struct Node {
        Node* left = nullptr;
        Node* right = nullptr;
        Node* parent = nullptr;
        int64_t sum = 0;
        int64_t a = -1;
        int64_t b = -1;
    };
    Node top {nullptr, nullptr, nullptr, 0, -1073741824, 1073741824};
    void update(Node* x) {
        Node* temp = x;
        while ((temp->a != -1073741824) || (temp->b != 1073741824)) {
            temp = temp->parent;
            temp->sum = 0;
            if (temp->left != nullptr)
                temp->sum += temp->left->sum;
            if (temp->right != nullptr)
                temp->sum += temp->right->sum;
        }
    }
public:
    void add(int64_t& x) {
        Node* temp = &top;
        while (temp->a != temp->b - 1) {
            if (x < (temp->a + temp->b) / 2) {
                if (temp->left == nullptr) {
                    Node* NewNode = new Node;
                    NewNode->parent = temp;
                    NewNode->a = temp->a;
                    NewNode->b = (temp->a + temp->b) / 2;
                    temp->left = NewNode;
                }
                temp = temp->left;
            } else {
                if (temp->right == nullptr) {
                    Node* NewNode = new Node;
                    NewNode->parent = temp;
                    NewNode->a = (temp->a + temp->b) / 2;
                    NewNode->b = temp->b;
                    temp->right = NewNode;
                }
                temp = temp->right;
            }
        }
        temp->sum = 1;
        update(temp);
    }
    void remove(int64_t& x) {
        Node* temp = &top;
        while (temp->a != temp->b - 1) {
            if (x < (temp->a + temp->b) / 2) {
                temp = temp->left;
            } else {
                temp = temp->right;
            }
        }
        temp->sum = 0;
        update(temp);
    }
    int64_t goBot(Node* x) {
        Node* temp = x;
        while ((temp->left != nullptr) || (temp->right != nullptr)) {
            if ((temp->right != nullptr) && (temp->right->sum >= 1)) {
                temp = temp->right;
            } else {
                temp = temp->left;
            }
        }
        return temp->a;
    }
    int64_t kStat(int64_t& x) {
        int64_t k = x - 1;
        Node* temp = &top;
        while (k != 0) {
            if ((temp->right != nullptr) && (temp->right->sum > k)) {
                temp = temp->right;
            } else if ((temp->right != nullptr) && (temp->right->sum <= k)) {
                k -= temp->right->sum;
                temp = temp->left;
            } else if (temp->right == nullptr) {
                temp = temp->left;
            }
        }
        k = goBot(temp);
        return k;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    DerOtr tree;
    int64_t n, var, sw;
    cin >> n;
    for (int64_t i = 0; i < n; ++i) {
        cin >> sw;
        cin >> var;
        switch (sw) {
            case 1:
                tree.add(var);
                break;
            case -1:
                tree.remove(var);
                break;
            case 0:
                cout << tree.kStat(var) << '\n';
                break;
            default:
                break;
        }
    }
    return 0;
}
