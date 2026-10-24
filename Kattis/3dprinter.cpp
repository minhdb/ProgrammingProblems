#include <iostream>
#include <cmath>

using namespace std;
using ll = long long;
int main()
{
    ll n, printers=1;
    cin >> n;
    if (n <= 2) {
        cout << n << "\n";
        return 0;
    }
    ll min_days = numeric_limits<ll>::max();
    while(pow(2,printers) < n) {
        ll cur_min_days = printers + ceil(n * 1.0/pow(2, printers));
        min_days = min(cur_min_days, min_days);
        printers++;
    }
    cout << min_days << "\n";
    return 0;
}
