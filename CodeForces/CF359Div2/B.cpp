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

bool cmp(vector<int> & a, vector<int> & b) {
    if (a.size() != b.size()) return false;
    else {
        for (int i = 0; i < a.size(); i++) {
            if (a[i] != b[i]) return false;
        }
    }
    return true;
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    vector<int> a_sorted = a;
    sort(a_sorted.begin(), a_sorted.end());

    while(!cmp(a, a_sorted)) {
        for (int i = 1; i < n; i++) {
            if (a[i] < a[i-1]) {
                swap(a[i], a[i-1]);
                cout << i << " " << i+1 << endl;
            }
        }
    }
    return 0;
}
