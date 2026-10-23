#include <iostream>

using namespace std;

int main()
{
    unsigned short n;
    int k;
    cin >> n >> k;
    unsigned short a_i;
    unsigned int days = 0;
    unsigned candies_cur = 0;
    for (unsigned short i = 0; i < n; i++) {
        cin >> a_i;
        candies_cur += a_i;
        if (candies_cur >= 8) {
            k -= 8;
            candies_cur -= 8;
        } else { 
            k -= candies_cur;
            candies_cur = 0;
        }
        days++;
        if (k <= 0) {
            cout << days << endl;
            return 0;
        }
    }

    if (k > 0) cout << "-1" << endl;
    return 0;
}
