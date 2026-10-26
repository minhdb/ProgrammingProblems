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
    int k,l,m,n,d,c;
    cin >> k >> l >> m >> n >> d;
    for (int i = 1; i < d + 1; i++) {
        if (i % k == 0 ||
                i % l == 0 ||
                i % m == 0 ||
                i % n == 0)
            c++;
    }

    cout << c << endl;

    return 0;
}
