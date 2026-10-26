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
 * Problem: Codeforces 236A
 * Minh Bui
 */

using namespace std;

int main() {
    string s; cin >> s;
    char ascii[26];

    for (int i = 0; i < 26; i++) ascii[i] = 0;

    for (int i = 0; i < s.size(); i++) {
        ascii[s[i] - 'a']++;
    }

    int count = 0;
    for (int i = 0; i < 26; i++) 
        if (ascii[i] != 0) count++;

    if (count % 2) cout << "IGNORE HIM!" << endl;
    else cout << "CHAT WITH HER!" << endl;

    return 0;
}
