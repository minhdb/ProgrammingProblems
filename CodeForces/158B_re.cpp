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
#include <string.h>
#define vi vector<int>
#define vii vector< vector <int> >
#define FOR(x, size) for(int x = 0; x < size; ++x)

/*
 * Problem: 158B.
 * Minh Bui
 */

using namespace std;


int main() {
    int n, c[5], s = 0;
    memset(c, 0, sizeof(int) * 5);
    cin >> n;
    while(n--) { cin >> s; c[s]++;} s = 0;
    s += c[4]; s += c[2] / 2;
    if (c[2] % 2 == 0) c[2] = 0;
    else { c[2] = 1; }

    int k = min(c[1], c[3]); s += k;
    c[1] -= k; c[3] -= k;

    if (c[1]) {
        if (c[2]) {
            s += 1; c[1] -= 2;
            c[2] = 0;
        }
    } else if (c[3]) 
        s += c[3];
    s += c[2];
    if (c[1] > 0) {
        if (c[1] % 4 == 0) s += c[1]/4;
        else s += c[1]/4 + 1;
    }
    cout << s << endl;
    return 0;
}

