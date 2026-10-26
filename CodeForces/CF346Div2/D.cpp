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
 * Problem: D
 * Minh Bui
 */

using namespace std;

bool checkLeft(char init, char turn) {
    return ((init == 'n' && turn == 'w') || 
            (init == 'w' && turn == 's') ||
            (init == 's' && turn == 'e') ||
            (init == 'e' && turn == 'n'));
}

int main() {
    int n, x, y, c = 0;
    vector< pair <int, int> > points;
    FOR(i, n) {
        cin >> x >> y;
        points.push_back(make_pair(x, y));
    }
    cin >> x >> y;
    points.push_back(make_pair(x, y));
    
    char dir = 'n';
    char change;
    pair <int, int> p_1 = points[0];
    for (int i = 1; i < points.size(); i++) {
        pair <int, int> p_2 = points[i];
        if (p_2.first - p_1.first > 0) {
            change = 'e';
        } else if (p_2.first - p_1.first < 0) {
            change = 'w';
        } else {
            if (p_2.second - p_1.second > 0)
             change = 'n';
             else change = 's';
        }
        if (checkLeft(dir, change)) c++;
        dir = change;
        p_1 = p_2;
    }
    
    cout << c << endl;
    return 0;
}
