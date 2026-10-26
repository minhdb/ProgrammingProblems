#include <iostream>

using namespace std;

int main() {
    int a, b, c;
    cin >> a >> b >> c;
    // a + ck = b
    if ((b - a) == 0 || ((c != 0) && 
            (((b - a) % c + c) % c == 0 && (b - a) / c > 0)))
        cout << "YES" << endl;
    else cout << "NO" << endl;
    return 0;
}
