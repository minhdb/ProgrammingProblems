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
 * Problem: SRM 688 Division 2 level 1.
 * Minh Bui
 */

using namespace std;

class ParenthesesDiv2Easy {
    public:
        int getDepth(string s);
};

int ParenthesesDiv2Easy::getDepth(string s) {
    int maxD = 0, count = 0;
    stack <char> st;

    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == '(') {
            st.push('('); 
            count++;
            maxD = max(count, maxD);
        } else {
            st.pop(); count--;
        }
    }
    return maxD;
}
