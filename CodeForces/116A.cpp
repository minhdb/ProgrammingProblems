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
 * Problem: Codeforces 116A
 * Minh Bui
 */

using namespace std;

int main() {
    int n, a, b, min = 0, on = 0;
    cin >> n;
    while(n--) {
        cin >> a; cin >> b;
        on -= a; on += b;
        min = max(min, on);
    }
    cout << min << endl;
    return 0;
}
