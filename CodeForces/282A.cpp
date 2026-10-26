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
#define vi vector<int>
#define vii vector< vector <int> >
#define gc getchar_unlocked
#define FOR(x, size) for(int x = 0; x < size; ++x)

/*
 * Problem: Codeforce 282A
 * Minh Bui
 */

using namespace std;

int main() {
    int n, x, i;
    string s;
    x = i = 0;
    scanf("%d", &n);
    while (n--) {
        cin >> s;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '-') {
                x--; break;
            } else if (s[i] == '+') {
                x++; break;
            } else continue;
        }
    }
    printf("%d\n", x);
    return 0;
}
