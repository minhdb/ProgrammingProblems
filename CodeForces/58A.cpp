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
 * Problem: Codeforces 58A
 * Minh Bui
 */

using namespace std;

int main() {
    string s; cin >> s;
    bool hello[5]; char last = '-';
    for (int i = 0; i < 5; i++) hello[i] = false;

    for (size_t i = 0; i < s.size(); i++)
    {
        if (s[i] == 'h') {
            hello[0] = true;
        } else if (s[i] == 'e' && hello[0]) {
            hello[1] = true;
        } else if (s[i] == 'l' && hello[1] && !hello[2]) {
            hello[2] = true;
        } else if (s[i] == 'l' && hello[2]) {
            hello[3] = true;
        } else if (s[i] == 'o' && hello[3]) {
            hello[4] = true;
        }
    }
    for (int i = 0; i < 5; i++)
        if (!hello[i]) {cout << "NO" << endl; return 0;}
    cout << "YES" << endl;
    return 0;
}
