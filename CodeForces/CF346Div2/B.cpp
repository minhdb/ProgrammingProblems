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
#include <stdlib.h>
#define vi vector<int>
#define vii vector< vector <int> >
#define FOR(x, size) for(int x = 0; x < size; ++x)

/*
 * Problem:B
 * Minh Bui
 */

using namespace std;

const int maxN = 1000000;
vector< pair <int, string> > *t = new vector<pair <int, string> >[maxN + 1];
int main() {
    int n, m, s, r;
    string name;
    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        cin >> name >> r >> s;
        t[r-1].push_back(make_pair(s, name));
    }

    /*
     * n = 100000; m = 1; r = 1;
     * for (int i = 0; i < n; i++) {
     *     s = rand() % 801;
     *     t[r-1].push_back(make_pair(s, to_string(i)));
     *     cout << "Added: " << to_string(i) << " " << s <<endl;
     * }
     */
    for (int i = 0; i < m; i++) {
        // cout << "Accessing element at: " << i << endl;
        vector < pair <int, string > > r = t[i];
        // cout << "Still here." << endl;
        sort(r.rbegin(), r.rend());
        // cout << "Sorting complete." <<endl;
        if (r.size() > 2)
            if (r[1].first == r[2].first) { 
                cout << "?" << endl; continue;}
        cout << r[0].second << " " << r[1].second << endl;
    }
    return 0;
}
