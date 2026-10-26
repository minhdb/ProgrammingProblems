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
 * Problem: 677B Codeforces
 * Minh Bui
 */

using namespace std;

int main() {
    int n, h, k, s, a, r;
    cin >> n >> h >> k;
    s = 0; r = 0;
    while(n--) {
        cin >> a;
        if (a + r <= k) {
            r += a;
            continue;
        } else {
            if (a + r > h) {
                s += ceil((a + r) / k * 1.0);
                continue;
            }
            s++;
            if (a > k)
                r += (a-k);
            else {
                if (r >= (k-a))
                    r -= (k - a);
                else r = 0;
            }
        }
    }
    if (r > 0) s += ceil(r / (k * 1.0));
    cout << s << endl;
    return 0;
}
