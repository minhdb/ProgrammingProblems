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
 * Problem: SRM 688 Division 2 level 2.
 * Minh Bui
 */

using namespace std;

class ParenthesesDiv2Medium {
    public:
        vector <int> correct(string s);
};

vector <int> ParenthesesDiv2Medium::correct(string s) {
    vector <int> r;
    int open = 0, close = 0, n = s.size();
    for (int i = 0; i < s.size(); i++) {
        if (open == close && s[i] == ')') {
            r.push_back(i);
            open++;
            continue;
        }
        if (open == n/2 && s[i] == '(') {
            r.push_back(i);
            continue;
        }
        if (s[i] == '(') open++;
        else close++;
    }
    return r;
}