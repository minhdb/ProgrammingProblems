#include <iostream>
using namespace std;
using ll = long long;

int main()
{
    ll a {-1}, b{-1};
    int i {1};
    while (a != 0 && b != 0) {
        cin >> a >> b;
        if (a != 0 && b != 0) {
            ll result = ((a * (a - 1)) / 2) * ((b * (b - 1) / 2));
            cout << "Case " << i << ": " << result << "\n";
        }
        i++;
    }
    return 0;
}
