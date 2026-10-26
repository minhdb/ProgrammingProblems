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
 * Problem: Codeforces 131A.
 * Minh Bui
 */

using namespace std;

bool all_upper(string &s) {
    for (size_t i = 0; i < s.size(); i++)
        if (!isupper(s[i])) return false;
    return true;
}

bool first_lower(string &s) {
    if (isupper(s[0])) return false;
    for (size_t i = 1; i < s.size(); i++)
        if (!isupper(s[i])) return false;
    return true;
}

int main() {
    string s;
    cin >> s;
    if (all_upper(s)) {
        for (size_t i = 0; i < s.size(); i++)
            printf("%c", tolower(s[i]));
    } else if (first_lower(s)) {
        printf("%c", toupper(s[0]));
        for (size_t i = 1; i < s.size(); i++)
            printf("%c", tolower(s[i]));
    } else
        cout << s;
    cout << endl;

    return 0;
}
