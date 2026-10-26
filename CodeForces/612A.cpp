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
 * Problem: Codeforces 612A
 * Minh Bui
 */

using namespace std;

int main() {
    int n, p, q; string s;
    cin >> n; cin >> p; cin >> q; cin >> s;
    int i, j;
    for (i = 0; i < 101; i++) {
        for (j = 0; j < 101; j++) {
            if ((i * p + j * q) == n) {
                int f = 0;
                cout << i + j << endl;
                FOR(x, i){ cout << s.substr(f, p) << endl; f += p; }
                FOR(x, j){ cout << s.substr(f, q) << endl; f += q; }
                return 0;
            }
        }
    }
    cout << -1 << endl;
    return 0;
}
