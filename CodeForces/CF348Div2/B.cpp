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
    int n, r, pos = 0, neg = 0;
    string s, f = "FINITE", inf = "INFINITE";
    vector<int> d;
    cin >> n >> s;
    for (int i = 0; i < n; i++) {
        cin >> r;
        if (s[i] == '>') d.push_back(r);
        else d.push_back(-r);
    }
    
    int sum = 0;
    for (int i = 0; i < d.size(); i++) {
        sum += d[i];
    }

    if (sum > 0 && sum <= n) cout << inf << endl;
    else cout << f << endl;
    
    return 0;
}
