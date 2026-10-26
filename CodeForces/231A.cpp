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
#define FOR(x, size) for(int x = 0; x < size; ++x)

/*
 * Problem: 231A Codeforces
 * Minh Bui
 */

using namespace std;

int main() {
    int n, p, v, t, c;
    scanf("%d", &n);
    c = 0;
    while(n--) {
        scanf("%d %d %d", &p, &v, &t);
        if ((p && v) || (v && t) || (p && t)) c++;
    }
    printf("%d\n", c);
    return 0;
}
