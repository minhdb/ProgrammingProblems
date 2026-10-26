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
 * Problem: UVA00514 - Rails
 * Minh Bui
 */

using namespace std;

bool possible(vector<int> &a, vector<int> &target) {
    vector<int> station, b;
    int n = a.size();
    for (int i = 0; i < target.size(); i++) {
        if (station.empty()) {
            int next = a.back();
            a.pop_back();
            station.push_back(next);
        } else {
            while (b.size() != n) {
                while (station.back() != target[i]) {
                    int nextA = a.back();
                    a.pop_back();
                    station.push_back(nextA);
                }
                b.push_back(station.back());
                station.pop_back();
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (b[i] != target[i]) return false;
    }
    return true;
}

int main() {
    int n = 1, e;
    while (n != 0) {
        cin >> n;
        if (n == 0) return 0;
        vector<int> a, target(n);
        for (int i = n; i > 0; i--) {
            a.push_back(i);
        }

        for (int i = 0; i < n; i++) {
            cin >> target[i];
        }
        if (possible(a, target)) cout << "Yes" << endl;
        else cout << "No" << endl;

        target.resize(0);
        int end;
        cin >> end;
        if (end != 0) {
            target.push_back(end);
            int readInt;
            for (int i = 1; i < n; i++) {
                cin >> readInt;
                target.push_back(readInt);
            }
            if (possible(a, target)) cout << "Yes" << endl;
            else cout << "No" << endl;
        }
        cout << endl;
    }
    return 0;
}
