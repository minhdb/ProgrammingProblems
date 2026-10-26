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
    string s; int c = 0;
    cin >> s;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '4' || s[i] == '7') c++;
    }

    if (c == 4 || c == 7) cout << "YES" << endl;
    else cout << "NO" << endl;

    return 0;
}
