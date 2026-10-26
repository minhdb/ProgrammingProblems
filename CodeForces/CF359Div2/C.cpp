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
string to7(int a) {
    string r = "";
    while (a / 7 != 0) {
        r += to_string(a % 7);
        a /= 7;
    }

    r += to_string(a%7);
    reverse(r.begin(), r.end());
    return r;
}

bool isDist(string a) {
    int d[7];
    memset(d, 0, sizeof(int)*7);
    if (a.size() > 7) return false;
    else {
        for (int i = 0; i < a.size(); i++) {
            if (d[a[i]-'0'] == 0) d[a[i]-'0']++;
            else return false;
        }
    }
    return true;
}

int main() {
    int n, m, c = 0;
    cin >> n >> m;
    int len_n = to7(n-1).size();
    int len_m = to7(m-1).size();
    if (len_n + len_m <= 7) {
        for (int i = 0; i < n; i++) {
            string hin7 = to7(i);
            if ((len_n - hin7.size() > 1)) continue;
            else {
            string h = string(len_n - hin7.size(), '0') + hin7;
                for (int j = 0; j < m; j++) {
                    string min7 = to7(j);
                    if (len_m - min7.size() > 1) continue;
                    else {
                        string mi = string(len_m - min7.size(), '0') + min7;
                        if (isDist(h+mi)) {
                            // cout << h + mi << endl;
                            c++;
                        }
                    }
                }
            }
        }
    }
    cout << c << endl;
    return 0;
}
