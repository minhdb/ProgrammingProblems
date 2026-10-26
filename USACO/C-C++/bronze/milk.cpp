/*
ID: minh.fo1
PROG: milk
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
#include <fstream>
#include <algorithm>
#include <cstring>
#define vi vector<int>
#define vii vector< vector <int> >
#define FOR(x, size) for(int x = 0; x < size; ++x)

/* Problem: milk USACO
 * Minh Bui
 */

using namespace std;

int main() {
    int n, m, p, a;
    ifstream fin ("milk.in");
    ofstream fout("milk.out");
    vector< pair <int, int> > pr_lim;
    fin >> n >> m;
    while(m--) {
        fin >> p >> a;
        pr_lim.push_back(make_pair(p, a));
    }

    sort(pr_lim.rbegin(), pr_lim.rend());
    int minCost = 0;
    while(n > 0) {
        pair<int, int> cur = pr_lim.back();
        pr_lim.pop_back();
        if (n >= cur.second) {
            n -= cur.second;
            minCost += (cur.first * cur.second);
        } else {
            minCost += (cur.first * n);
            n = 0;
        }
    }
    fout << minCost << endl;
    return 0;
}
