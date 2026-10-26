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

int main() {
    int n, c = 0, last = -1;
    cin >> n;
    while (n > 0) {
        if (last == 1) {
            if (n - 2 >= 0) {
                last = 2;
                n -= 2;
                c++;
            } else break;
        } else {
            if (n - 1 >= 0) {
                n -= 1;
                last = 1;
                c++;
            } else break;
        }
    }
    cout << c << endl;
    return 0;
}
