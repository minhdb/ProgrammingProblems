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
    int n, c = 0, d;
    unsigned long long x;
    cin >> n >> x;
    char op;
    while (n--) {
        cin >> op>> d;
        if (op == '+') x += d;
        else {
            if (x < d) c++;
            else x -= d;
        }
    }
    cout << x << " " << c << endl;
    return 0;
}
