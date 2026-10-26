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
 * Problem: Codeforces 122A
 * Minh Bui
 */

using namespace std;

int main() {
    int n; cin >> n;
    int luck[12] = {4, 7, 47, 74, 444, 447, 474, 477, 744, 747, 774, 777};
    for (int i = 0; i < 12; i++) {
        if (n % luck[i] == 0) {cout << "YES" << endl; return 0;}
    }
    cout << "NO" << endl;
    return 0;
}
