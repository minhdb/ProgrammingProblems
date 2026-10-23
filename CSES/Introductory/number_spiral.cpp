#include <iostream>
#include <algorithm>

using std::cin;
using std::cout;
using std::max;

int main()
{
    // if m is odd
    // g[y][x] = m**2 - (x-1) - (m-y)
    // if m is even
    // g[y][x] = m**2 - (y-1) - (m-x)
    long long y,x,t;
    cin >> t;
    for (long long i = 0; i < t; i++) {
        cin >> y >> x;
        long long m = max(x,y);
        long long result = 0;
        if (m % 2 == 0) {
            result = m*m - (x-1) - (m-y);
        } else {
            result = m*m - (y-1) - (m-x);
        }
        cout << result << "\n";
    }

    return 0;
}

