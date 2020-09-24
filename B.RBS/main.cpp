#include <iostream>
#include <stack>

using std::cin;
using std::cout;
using std::stack;
using std::string;
using std::endl;

int main()
{
    stack <char> st;
    string s;
    getline(cin, s);
    if (s == ""){
        cout << "yes" << endl;
        return 0;
    }
    for (unsigned long long i = 0; i < s.length(); ++i){
        if ((s[i]=='{')||(s[i]=='[')||(s[i]=='(')) {
            st.push(s[i]);
        } else  if (st.empty()){
            cout << "no" << endl;
            return 0;
        } else if (((st.top() == '{') && (s[i] == '}')) || ((st.top() == '(') && (s[i] == ')')) || ((st.top() == '[') && (s[i] == ']'))){
            st.pop();
        } else {
            cout << "no" << endl;
            return 0;
        }
    }
    if (st.empty()){
        cout << "yes" << endl;
    } else {
        cout << "no";
    }
    return 0;
}
