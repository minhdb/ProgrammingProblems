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
 * Problem: SRM 155 Div II Level 1
 * Quipu TopCoder
 * Minh Bui
 */

using namespace std;

class Quipu {
    public:
    int readKnots(string knots) {
        int _ = 1;
        int c = 1;
        char prev = 'X';
        string num = "";
        for (size_t i = 2; i < knots.size(); i++) {
            if (knots[i] == '-') {
                if (prev == '-') _++;
                else {
                    if (c > 0) num += to_string(c);
                    c = 0;
                    _ = 1;
                }
            } else {
                if (prev == 'X') c++;
                else {
                    if (_ - 1 > 0) {
                        for (int j = 0; j < _ - 1; j++)
                            num += '0';
                    }
                    c = 1;
                    _ = 0;
                }
            }
            prev = knots[i];
        }
        if (prev == '-') {
            if (_ - 1 > 0) {
                        for (int j = 0; j < _ - 1; j++)
                            num += '0';
                    }
        } else {
            if (c > 0) num += to_string(c);
        }
        return stoi(num);
    }
};

int main() {
    return 0;
}
