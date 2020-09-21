#include <iostream>

using std::cout;
using std::cin;
using std::stoi;
using std::endl;
using std::string;

struct Stack{
    private:
       struct Node{
        int value;
        Node *last;
    };
    int size = 0;
    Node *root = nullptr;
    public:
    void push(int v){
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
            int ans = root->value;
            Node *temp = root;
            root = temp->last;
            delete(temp);
            cout << ans << endl;
        }
    }
    void Back(){
        if (!size){
            cout << "error" << endl;
        } else {
            int ans = root->value;
            cout << ans << endl;
        }
    }
    void Size(){
        cout << size << endl;
    }
    void Clear(){
        while(!(root->last == NULL)){
            --size;
            Node *temp = root;
            root = temp->last;
            delete temp;
        }
        --size;
        delete root;
        cout << "ok" << endl;
    }
};

int main() {
    Stack st;
    string str;
    while(true){
        getline(cin, str);
        switch(str[0]){
            case 'b':
                st.Back();
                break;
            case 'e':
                cout << "bye" << endl;
                return 0;
                break;
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
                    string tmp;
                    unsigned int i = 5;
                    bool f = false;
                    if (str[i] == '-'){
                        ++i;
                        f = true;
                    }
                    for(; i < str.length(); ++i){
                        tmp[i - 5 - f] = str[i];
                    }
                    int vtmp;
                    vtmp = stoi(tmp);
                    if(f){
                        vtmp = -vtmp;
                    }
                    st.push(vtmp);
                }
                break;
        }
    }
    return 0;
}
