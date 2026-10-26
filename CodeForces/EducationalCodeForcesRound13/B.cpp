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
 * Problem:
 * Minh Bui
 */

using namespace std;

int oddD(int y) {
    if ((y % 400 == 0) || (y % 4 == 0 && y % 100 != 0))
        return 2;
    else return 1;
}

int main() {
    int y;
    cin >> y;
    int countOdd = oddD(y);
    if (countOdd == 2) cout << y + 28 << endl;
    else {
        while(true) {
            ++y;
            countOdd += oddD(y);
            cout << y << " " <<  countOdd << endl;
            if (countOdd == 7) continue;
            else if (countOdd % 7 == 0) break;
        }
        cout << y + 1 << endl;
    }
    return 0;
}
