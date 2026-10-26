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
 * Problem: Codeforces 266A.
 * Minh Bui
 */

using namespace std;

int main() {
    int n; string s;
    scanf("%d", &n); cin >> s;
    char last = 'A'; int c = 0;
    for (int i = 0; i < s.size(); i++) {
        if (last == s[i]) c++;
        else last = s[i];
    }
    cout << c << endl;
    return 0;
}
