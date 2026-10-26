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
 * Problem: Codeforces 96A
 * Minh Bui
 */

using namespace std;

int main() {
    int z, o = 0;
    string s;
    cin >> s;
    FOR(x, s.size()) {
        if ((int) s[x] - '0') {
            o++; z = 0;
            if (o >= 7) {cout << "YES" << endl; return 0;}
        } else {
            z++; o = 0;
            if (z >= 7) {cout << "YES" << endl; return 0;}
        }
    }
    cout << "NO" << endl;
    return 0;
}
