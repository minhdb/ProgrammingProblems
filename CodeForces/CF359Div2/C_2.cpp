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
    int n, m;
    cin >> n >> m;

    int len_n = 1, len_m = 1;
    for (int i = 7; i < n; i *= 7) len_n++;
    for (int i = 7; i < m; i *= 7) len_m++;

    int count = 0;
    if (len_n + len_m <= 7) {
        for (int i = 0; i != n; i++) {
            for (int j = 0; j != m; j++) {
            vector<int> used(7, 0);

            for (int a = i, k = 0; k != len_n; a /= 7, k++) 
                used[a % 7]++;

            for (int b = j, k = 0; k != len_m; b /= 7, k++) {
                used[b % 7]++;
            }

            if (*max_element(used.begin(), used.end()) <= 1) count++;
            }
        }
    }

    cout << count << endl;
    return 0;
}
