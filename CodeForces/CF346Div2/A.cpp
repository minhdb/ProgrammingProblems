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
 * Problem: A
 * Minh Bui
 */

using namespace std;

int main() {
    int n, a, b, k;
    scanf("%d %d %d", &n, &a, &b);
    k = a;
    if (b > 0) {
        for (int i = 1; i <= b; i++) {
            k++;
            if (k > n) k = 1;
        }
    } else {
        for (int i = 1; i <= -b; i++) {
            k--;
            if (!k) k = n;
        }
    }
    cout << k << endl;
    return 0;
}
