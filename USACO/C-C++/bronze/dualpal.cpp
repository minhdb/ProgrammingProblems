/*
ID: minh.fo1
PROG: dualpal
LANG: C++11
*/

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
#include <fstream>
#define vi vector<int>
#define vii vector< vector <int> >
#define FOR(x, size) for(int x = 0; x < size; ++x)

/* Problem: dualpal
 * Minh Bui
 */

using namespace std;

string tenToB(int n, int b) {
    string result = "";
    while (n != 0) {
        result += to_string(n % b);
        n /= b;
    }
    reverse(result.begin(), result.end());
    return result;
}

bool checkPal(string s) {
    int i = 0, j = s.size() - 1;
    while (i < j) {
        if (s[i] != s[j]) return false;
        i++; j--;
    }
    return true;
}

int main() {
    ifstream fin ("dualpal.in");
    ofstream fout("dualpal.out");
    int n, s;
    fin >> n >> s;
    while (n > 0) {
        s++; int c = 0;
        for (int i = 2; i <= 10; i++) {
            string s_conv = tenToB(s, i);
            if (checkPal(s_conv)) {
                c++;
                if (c == 2) {
                    fout << s << endl;
                    n--; break;
                }
            }
        }
    }


    return 0;
}
