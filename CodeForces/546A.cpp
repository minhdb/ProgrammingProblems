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
 * Problem: Codeforces 546A
 * Minh Bui
 */

using namespace std;

int main() {
    int k, n, w;
    cin >> k >> n >> w;
    int b = k*w*(w+1)/2 - n;
    b > 0 ? cout << b << endl : cout << 0 << endl;
    return 0;
}
