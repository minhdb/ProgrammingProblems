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
 * Problem: Codeforces Round #357 Div 2.
 * Minh Bui
 */

using namespace std;

int main() {
    int n;
    string name;
    int b, a;
    cin >> n;
    bool found = false;
    while(n--) {
        cin >> name >> b >> a;
        if (b >= 2400 && (a - b) > 0) {
            cout << "YES" << endl;
            found = true;
            break;
        }
    }
    if (!found) cout << "NO" << endl;
    return 0;
}
