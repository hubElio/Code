#include <iostream>

using namespace std;

int main()
{
    int res,a(0),b(0);
    //int& ref(res);
    cout << "valeur de a :";
    cin >> a;
    cout << "valeur de b :";
    cin >> b;
    res = a+b;
    cout << "a+b = "<< res << endl;
    // << endl;// saut de ligne
    return 0;
}