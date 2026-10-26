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
 * Problem: Codeforces 160A.cpp
 * Minh Bui
 */

using namespace std;

int main() {
    int n, s = 0, c = 0; cin >> n;
    vector <int> coins(n);
    for (size_t i = 0; i < n; i++) {
        cin >> coins[i];
        s += coins[i];
    }
    n = 0; c = 0;
    sort(coins.begin(), coins.end());
    while (s >= n) {
        n += coins.back();
        s -= coins.back();
        coins.pop_back();
        c++;
    }
    cout << c << endl;
    return 0;
}
