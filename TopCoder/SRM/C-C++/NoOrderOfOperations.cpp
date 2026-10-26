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
 * Problem: SRM200 Div II Level 1.
 * TopCoder NoOrderOfOperations.
 * Minh Bui
 */

using namespace std;

class NoOrderOfOperations {
    public:
        int evaluate(string expr) {
            int result = expr[0] - '0';
            for (int i = 1; i < expr.size() - 1; i += 2) {
                char op = expr[i];
                int oper = expr[i+1] - '0';
                if (op == '*') result *= oper;
                else if (op == '+') result += oper;
                else result -= oper;
            }
            return result;
        }
};

int main() {
    return 0;
}
