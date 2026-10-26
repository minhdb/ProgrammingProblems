/**
 * CSES Two Knights
 * https://cses.fi/problemset/task/1072/
 * The solution is the total possible positions C(2,n) minus
 * the number of attacking positions.
 */

#include <iostream>
using namespace std;
using ull = unsigned long long;
int main()
{
    ull n;
    cin >> n;
    for (ull i{1}; i <= n; i++)
        cout << i*i*(i*i - 1)/2 - 4*(i-2)*(i-1) << "\n";
}
