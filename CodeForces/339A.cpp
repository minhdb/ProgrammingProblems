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
 * Problem: Codeforces 339A
 * Minh Bui
 */

using namespace std;

int main() {
    string s; vi v;
    cin >> s;
    for (int i = 0; i < s.size(); i++)
        if (s[i] != '+') v.push_back(s[i] - '0');

    sort(v.begin(), v.end());
    for (int i = 0; i < v.size(); i++) {
        cout << v[i];
        if (i != v.size() - 1) cout << "+";
        else cout << endl;
    }
    return 0;
}
