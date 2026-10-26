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
 * Problem: C
 * Minh Bui
 */

using namespace std;


int main() {
    long long m, n, t;
    cin >> n; cin >> m;
    map<long long, bool> a;
    for (long long i = 0; i < n; i++) {
        cin >> t;
        a[t] = true;
    }

    int c = 0;
    vector<long long> b;
    for (long long i = 1; i < 200000; i++) {
        if (!a[i] && m - i >= 0) {
            b.push_back(i);
            c++;
            m -= i;
        }
    }
    cout << c << endl;
    for (int i = 0; i < c; i++) {
        if (i == c - 1) cout << b[i] << endl;
        else cout << b[i] << " ";
    }
    return 0;
}
