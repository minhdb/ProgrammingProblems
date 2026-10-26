/*
ID: minh.fo1
PROG: milk2
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

/* Problem: milk2 USACO
 * Minh Bui
 */

using namespace std;

int main() {
    int n, a, b;
    ifstream fin("milk2.in");
    ofstream fout("milk2.out");
    fin >> n;
    vector< pair <int, int> > segments;
    while(n--) {
        fin >> a >> b;
        segments.push_back(make_pair(a, b));
    }

    sort(segments.begin(), segments.end());
    /*
    for (int i = 0; i < segments.size(); i++) {
        fout << segments[i].first << " " << segments[i].second << endl;
    }*/
    int cont = segments[0].second - segments[0].first; 
    int idle = 0;
    pair<int, int> tmp = segments[0];
    for (int i = 1; i < segments.size(); i++) {
        pair<int, int> cur = segments[i];
        if (cur.first >= tmp.first && cur.first <= tmp.second) {
            if (cur.second > tmp.second) tmp.second = cur.second;
            cont = max(cont, tmp.second - tmp.first);
        } else {
            idle = max(idle, cur.first - tmp.second);
            tmp = cur;
        }
    }
    fout << cont << " " << idle << endl;
    return 0;
}
