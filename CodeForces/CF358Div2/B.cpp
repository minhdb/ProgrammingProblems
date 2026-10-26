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

int find_mex(vector<int> a) {
    int v = a[a.size()-1]-1;
    for (int i = a.size() - 2; i >= 0; i--) {
        if (v != a[i]) return v;
        v--;
    }
    if (v <= a[0]) return a[a.size()-1]+1;
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n;i++) {
        cin >> a[i];
    }
    
    
    sort(a.begin(), a.end());
    cout << find_mex(a) << endl;
    
    return 0;
}
