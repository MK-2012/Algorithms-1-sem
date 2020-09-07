#include <iostream>
#include <cstdlib>
#include <climits>

using namespace std;


int main()
{
    string str;
    long long a = 0;
    long long R = 1000000;
    long long k = 0;
    getline(cin, str);
    cin >> a;
    long l[str.length()];
    for (long long i = 0; i < str.length(); i++){
        l[i] = -1;
    }
    for(long long i = 0; i < str.length(); i++){
        if(str[i] == 'R')
            R = i;
        if(str[i] == 'r'){
            l[i] = i - R - 1;
            R = 1000000;
        }
    }
    qsort(l, str.length(), sizeof(long long), [](const void* a, const void* b)
    {
        long long arg1 = *static_cast<const long long*>(a);
        long long arg2 = *static_cast<const long long*>(b);

        if(arg1 < arg2) return -1;
        if(arg1 > arg2) return 1;
        return 0;

    //  return (arg1 > arg2) - (arg1 < arg2); // possible shortcut
    //  return arg1 - arg2; // erroneous shortcut (fails if INT_MIN is present)
    });
    long long i = 0;
    while(l[i] <= -1)
        i ++;
    while (a - l[i] >= 0){
        k++;
        a -= l[i];
        i++;
    }
    cout << k;
    return 0;
}
