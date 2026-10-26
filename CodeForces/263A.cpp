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
 * Problem: Codeforces 263A
 * Minh Bui
 */

using namespace std;

int main() {
    string r; int row = 0, count = 0;
    for (int j = 0; j < 5; j++) {
        for (int k = 0; k < 5; k++)
        {
            string c;
            cin >> c;
            r += c;
        }
        int i = r.find('1');
        if (i >= 0) {
            count += abs(2 - i);
            count += abs(2 - row);
            break;
        }
        row++;
        r = "";
    }
    cout << count << endl;
    return 0;
}
