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

bool solve(int n) {
    int a = 0, b = 0;
    for (a = 0; a <= (n / 1234567); a++) {
        for (b = 0; b <= (n / 123456); b++) {
            int s = n - a * 1234567 - b * 123456;
            if (s >= 0 && s % 1234 == 0)
                return true;
        }
    }
    return false;
}

int main() {
    int n;
    cin >> n;
    if (solve(n))
        cout << "YES" << endl;
    else cout << "NO" << endl;
    return 0;
}
