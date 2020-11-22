#include <iostream>

using std::cin, std::cout;

template <typename T>
void swap(T &a, T &b) {
    T c = std::move(b);
    b = std::move(a);
    a = std::move(c);
}

class SplayTree {
private:
    struct Node {
        Node* left = nullptr;
        Node* right = nullptr;
        Node* parent = nullptr;
        bool isLeft = false;
        int64_t val = 0;
        int64_t sum = 0;
    };
    Node nothing {nullptr, nullptr, nullptr, false, -1, -1};
    void zig(Node& x) {
        x.parent->sum -= x.sum;
        x.sum += x.parent->val;
        if (x.isLeft) {
            if (x.parent->right != nullptr)
                x.sum += x.parent->right->sum;
            Node* right = x.right;
            if (right != nullptr) {
                right->isLeft = true;
                right->parent = x.parent;
            }
            x.parent->left = right;
            x.right = x.parent;
            x.parent = x.parent->parent;
            x.right->parent = &x;
            if (x.right->isLeft) {
                x.parent->left = &x;
            } else {
                x.parent->right = &x;
            }
            x.isLeft = x.right->isLeft;
            x.right->isLeft = false;
            if (x.right->left != nullptr) {
                x.right->sum += x.right->left->sum;
            }
        } else {
            if (x.parent->left != nullptr)
                x.sum += x.parent->left->sum;
            Node* left = x.left;
            if (left != nullptr) {
                left->isLeft = false;
                left->parent = x.parent;
            }
            x.parent->right = left;
            x.left = x.parent;
            x.parent = x.parent->parent;
            x.left->parent = &x;
            if (x.left->isLeft) {
                x.parent->left = &x;
            } else {
                x.parent->right = &x;
            }
            x.isLeft = x.left->isLeft;
            x.left->isLeft = true;
            if (x.left->right != nullptr) {
                x.left->sum += x.left->right->sum;
            }
        }
    }
    void zigzig(Node& x) {
        zig(*x.parent);
        zig(x);
    }
    void zigzag(Node& x) {
        zig(x);
        zig(x);
    }
    void splay(Node& x) {
        while (x.parent->val != -1) {
            if (x.isLeft) {
                if (x.parent->parent->val == -1) {
                    zig(x);
                } else if (x.parent->isLeft) {
                    zigzig(x);
                } else {
                    zigzag(x);
                }
            } else {
                if (x.parent->parent->val == -1) {
                    zig(x);
                } else if (!x.parent->isLeft) {
                    zigzig(x);
                } else {
                    zigzag(x);
                }
            }
        }
    }
    void split(int64_t x) {
        Node& temp = findM(x);
        if (nothing.right->val < x) {
            swap(nothing.right, nothing.left);
            nothing.left->isLeft = true;
            return;
        }
        if (temp.left != nullptr) {
            temp.sum -= temp.left->sum;
            nothing.left = temp.left;
            temp.left->parent = &nothing;
            temp.left = nullptr;
        }
    }
    void merge() {
        Node& temp = *nothing.right;
        while (temp.left != nullptr) {
            temp = *temp.left;
        }
        splay(temp);
        nothing.right->left = nothing.left;
        nothing.left->parent = nothing.right;
        nothing.left = nullptr;
        nothing.right->isLeft = false;
        nothing.left->isLeft = true;
        temp.sum += temp.left->sum;
    }
public:
    void add(int64_t x) {
        if (nothing.right != nullptr) {
            findM(x);
            if (nothing.right->val != x) {
                split(x);
                Node *NewNode = new Node;
                NewNode->val = x;
                if (nothing.right != nullptr) {
                    NewNode->right = nothing.right;
                    nothing.right->parent = NewNode;
                }
                NewNode->parent = &nothing;
                NewNode->isLeft = false;
                if (nothing.left != nullptr) {
                    NewNode->left = nothing.left;
                    nothing.left->parent = NewNode;
                    nothing.left = nullptr;
                }
                nothing.right = NewNode;
                NewNode->sum = NewNode->val;
                if (NewNode->right != nullptr)
                    NewNode->sum += NewNode->right->sum;
                if (NewNode->left != nullptr)
                    NewNode->sum += NewNode->left->sum;
            }
        } else {
            Node* NewNode = new Node;
            NewNode->val = x;
            NewNode->sum = x;
            nothing.right = NewNode;
            NewNode->isLeft = false;
            NewNode->parent = &nothing;
        }
    }
    Node& find(int64_t x) {
        Node* temp = nothing.right;
        while (temp->val != x) {
            if ((temp->left != nullptr) && (temp->val > x)) {
                temp = temp->left;
            } else if (((temp->left == nullptr) && (temp->val > x)) || ((temp->right == nullptr) && (temp->val < x))) {
                splay(*temp);
                return *(nothing.right);
            } else if ((temp->right != nullptr) && (temp->val < x)) {
                temp = temp->right;
            }
        }
        splay(*temp);
        return *(nothing.right);
    }
    Node& findM(int64_t x) {
        if (nothing.right == nullptr) {
            return nothing;
        }
        Node* temp = nothing.right;
        Node* min = temp;
        bool f = false;
        if (temp->val < x) {
            f = true;
        }
        while (temp->val != x) {
            if ((temp->left != nullptr) && (temp->val > x)) {
                temp = temp->left;
                if (((temp->val >= x) && (temp->val < min->val)) || ((f) && (temp->val >= x))) {
                    min = temp;
                    f = false;
                }
            } else if (((temp->left == nullptr) && (temp->val > x)) || ((temp->right == nullptr) && (temp->val < x))) {
                if (((temp->val >= x) && (temp->val < min->val)) || ((f) && (temp->val >= x))) {
                    min = temp;
                    f = false;
                }
                splay(*min);
                return *(nothing.right);
            } else if ((temp->right != nullptr) && (temp->val < x)) {
                temp = temp->right;
                if (((temp->val >= x) && (temp->val < min->val)) || ((f) && (temp->val >= x))) {
                    min = temp;
                    f = false;
                }
            }
        }
        splay(*min);
        return *(nothing.right);
    }
    Node& findL(int64_t x) {
        if (nothing.right == nullptr) {
            return nothing;
        }
        Node* temp = nothing.right;
        Node* max = temp;
        bool f = false;
        if (temp->val > x) {
            f = true;
        }
        while (temp->val != x) {
            if ((temp->left != nullptr) && (temp->val > x)) {
                temp = temp->left;
                if (((temp->val <= x) && (temp->val > max->val)) || ((f) && (temp->val <= x))) {
                    max = temp;
                }
            } else if (((temp->left == nullptr) && (temp->val > x)) || ((temp->right == nullptr) && (temp->val < x))) {
                if (((temp->val <= x) && (temp->val > max->val)) || ((f) && (temp->val <= x))) {
                    max = temp;
                }
                splay(*max);
                return *(nothing.right);
            } else if ((temp->right != nullptr) && (temp->val < x)) {
                temp = temp->right;
                if (((temp->val <= x) && (temp->val > max->val)) || ((f) && (temp->val <= x))) {
                    max = temp;
                }
            }
        }
        splay(*max);
        return *(nothing.right);
    }
    int64_t sum(int64_t l, int64_t r) {
        int64_t k = 0;
        Node x = findM(l);
        if ((x.val >= l) && (x.val <= r)) {
            k = x.val;
            if (x.right != nullptr) {
                k += x.right->sum;
            }
        }
        x = findL(r);
        if ((x.right != nullptr) && (x.val <= r) && (x.val >= l))
            k -= x.right->sum;
        return k;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int64_t n = 0;
    SplayTree tree;
    int64_t res = 0;
    cin >> n;
    for (int64_t i = 0; i < n; ++i) {
        char t;
        cin >> t;
        if (t == '+') {
            int64_t a;
            cin >> a;
            tree.add((a + res) % 1000000000);
            res = 0;
        } else {
            int64_t l, r;
            cin >> l >> r;
            res = tree.sum(l, r);
            cout << res << '\n';
        }
    }
    return 0;
}