#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <functional>
#include <numeric>
#include <utility>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>
#include <stdio.h>
#include <algorithm>
#include <cstring>
#define vi vector<int>
#define vii vector< vector <int> >
#define FOR(x, size) for(int x = 0; x < size; ++x)

/*
 * Problem: Codeforce 535A
 * Minh Bui
 */

using namespace std;

string m[16] = {"zero", "one", "two", "three", "four", "five", "six", "seven","eight", "nine", "ten",
"eleven", "twelve", "thirteen", "fourteen", "fifteen"};

string m_10[6] = {"", "", "twen", "thir", "for", "fif"};

string to_text(int n) {
    string s = "";
    if (n / 10 >= 6 && n / 10 <= 9) {
        if (n/10 == 8) s += m[n/10] + "y";
        else    s += m[n/10] + "ty";
        if (n % 10 != 0) s += ("-" + m[n % 10]);
    } else {
        if (n / 10 == 0) s += m[n%10];
        else if (n / 10 == 1) {
            if (n >= 10 && n <= 15) s = m[n];
            else  {
                if (n == 18) s += m[n%10] + "een";
                else s += m[n%10] + "teen";

            }
        }
        else if (n/10 >= 2 && n/10 <= 5) {
            s += (m_10[n/10] + "ty");
            if (n%10 != 0) s += ("-"+ m[n%10]);
        }
    }
    return s;
}

int main() {
    string s = "";
    int n;
    /*
     * for (int i = 1; i < 100; i++) {
     *     cout << i << + " " + to_text(i) << endl;
     * }
     */
    cin >> n;
    cout << to_text(n) << endl;
    return 0;
}
