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
 * Problem: Codeforces 112A
 * Minh Bui
 */

using namespace std;

int main() {
    string s1, s2;
    cin >> s1; cin >> s2;
    for (size_t i = 0; i < s1.size(); i++) {
        char c1 = tolower(s1[i]), c2 = tolower(s2[i]);
        if (c1 < c2) { cout << -1 << endl; return 0;}
        else if (c1 > c2) { cout << 1 << endl; return 0; }
        else continue;
    }
    cout << 0 << endl;

    return 0;
}
