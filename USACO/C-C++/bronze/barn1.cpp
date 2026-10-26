/*
ID: minh.fo1
PROG: barn1
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
#include <fstream>
#include <cstring>
#define vi vector<int>
#define vii vector< vector <int> >
#define FOR(x, size) for(int x = 0; x < size; ++x)

/* Problem: USACO barn1
 * Minh Bui
 */

using namespace std;

int main() {
    ifstream fin ("barn1.in");
    ofstream fout("barn1.out");
    int m, s, c, o, cur = 1, covered = 0;
    fin >> m >> s >> c;
    vector<int> holeWidths;
    while(c--) {
        fin >> o;
    }

    sort(holeWidths.begin(), holeWidths.end());

    while(m--) {
        covered += holeWidths.back();
        holeWidths.pop_back();
    }

    fout << covered << endl;
    return 0;
}
