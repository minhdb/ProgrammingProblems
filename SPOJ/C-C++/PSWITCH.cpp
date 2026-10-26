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
#include <bitset>
#define vi vector<int>
#define vii vector< vector <int> >
#define FOR(x, size) for(int x = 0; x < size; ++x)

/*
 * Problem: SPOJ PSWITCH - IOI 1998
 * Minh Bui
 */

int n;
using namespace std;

string flip(string &s) {
    string s_copy = s;
    for (int i = 0; i < s.size(); i++) {
        s[i] == '1' ? s_copy[i] = '0' : s_copy[i] == '1';
    }
    return s_copy;
}

string flipEven(string &s) {
    string s_copy = s;
    for (int i = 0; i < s.size(); i += 2) {
        s[i] == '1' ? s_copy[i] = '0' : s_copy[i] == '1';
    }
    return s_copy;
}

string flipOdd(string &s) {
    string s_copy = s;
    for (int i = 1; i < s.size(); i+= 2) {
        s[i] == '1' ? s_copy[i] = '0' : s_copy[i] = '1';
    }
    return s_copy;
}

string flipk(string &s) {
    string s_copy = s;
    for (int k = 0; 3 * k + 1 < s.size(); k++) {
        s[3*k+1] == '1' ? s_copy[3*k+1] = '0' : s_copy[3*k+1] = '1';
    }
    return s_copy;
}

bool check(string &s, vector<int> &on, vector<int> &off) {
    for (int i = 0; i < on.size(); i++) {
        if (!(s[on[i]]-'0')) return false;
    }

    for (int i = 0; i < off.size(); i++) {
        if ((s[off[i]]-'0')) return false;
    }
    return true;
}

int main() {
    int c, r;
    cin >> n >> c;
    string s(n, '1');
    vector<int> on, off;
    while(cin >> r && r != -1)
        on.push_back(r-1);

    while(cin >> r && r != -1)
        off.push_back(r-1);

    vector<string> possible;
    for (int i = 0; i < 2; i++) {
        if (i) s = flip(s);
        for (int j = 0; j < 2; j++) {
            if (j) s = flipOdd(s);
            for (int k = 0; k < 2; k++) {
                if (k) s = flipEven(s);
                for (int l = 0; l < 2; l++) {
                    if (l) s = flipk(s);
                    possible.push_back(s);
                }
            }
        }
    }
    int count = 0;
    sort(possible.begin(), possible.end());
    string prev = "";
    for (int i = 0; i < possible.size(); i++) {
        if (possible[i] != prev && check(possible[i], on, off)) {
        // if (possible[i] != prev) {
            cout << possible[i] << endl;
            count++;
        }
        prev = possible[i];
    }
    if (!count) cout << "Impossible" << endl;
    return 0;
}
