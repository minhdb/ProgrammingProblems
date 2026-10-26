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

int gcd(long a, long b) {
    long r;
    while (b != 0) {
        r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int main() {
    int n, c = 0, m;
    vector<long> a;
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> m; a.push_back(m);
    }

    long first = a[0];
    for (int i = 1; i < a.size(); i++) {
        if (gcd(first, a[i]) != 1) {
           c++;
           a.insert(a.begin() + i, 1);
           i++;
        }
        first = a[i];
    }

    cout << c << endl;
    for (int i = 0; i < a.size(); i++) {
        if (i == a.size() - 1) cout << a[i] << endl;
        else cout << a[i] << " ";
    }

    return 0;
}
