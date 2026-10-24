#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int h, p;
    cin >> h >> p;
    double incandescent_e_price = 60.0 * h * p / 100'000;
    double low_e_price = 11.0 * h * p / 100'000;
    
    unsigned int days = 0;
    
    while (true) {
        double low_total_price = 60.0 * ceil(h * days / 8000.0) + days * low_e_price;
        double incandescent_total_price = 5.0 * ceil(h * days / 1000.0) + days * incandescent_e_price;   
        if (low_total_price < incandescent_total_price) {
            break;
        }
        days++;
    }
    
    cout << days << "\n";
    
    return 0;
}
