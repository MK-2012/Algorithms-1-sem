#include <iostream>

using std::cout;
using std::cin;
using std::stoi;
using std::endl;
using std::string;

struct Stack{
private:
    struct Node{
        long long value;
        Node *last;
    };
    long long size = 0;
    Node *root = nullptr;
public:
    void push(long long v){
        ++size;
        Node *new_elem = new Node;
        new_elem->value = v;
        new_elem->last = root;
        root = new_elem;
        cout << "ok" << endl;
    }
    void pop(){
        if (!size){
            cout << "error" << endl;
        } else {
            --size;
            long long ans = root->value;
            Node *temp = root;
            root = temp->last;
            delete temp;
            cout << ans << endl;
        }
    }
    void Back(){
        if (!size){
            cout << "error" << endl;
        } else {
            cout << root->value << endl;
        }
    }
    void Size(){
        cout << size << endl;
    }
    void Clear(){
        while(size){
            --size;
            Node *temp = root;
            root = temp->last;
            delete temp;
        }
        cout << "ok" << endl;
    }
};

int main() {
    Stack st;
    string str;
    while(true){
        cin >> str;
        switch(str[0]){
            case 'b':
                st.Back();
                break;
            case 'e':
                cout << "bye" << endl;
                return 0;
            case 'c':
                st.Clear();
                break;
            case 's':
                st.Size();
                break;
            case 'p':
                if(str[1] == 'o'){
                    st.pop();
                } else {
                    long long vtmp;
                    cin >> vtmp;
                    st.push(vtmp);
                }
                break;
            default:
                cout << endl;
                break;
        }
    }
}
