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

using namespace std;
/*
 * Problem: SRM 688 Division 2 level 2.
 * Minh Bui
 */
class AttackOfTheClones {
    public:
    int count(vector <int> firstWeek, vector <int> lastWeek) {
        int result = 1; int n = firstWeek.size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (firstWeek[i] == lastWeek[j] && i > j)
                    result = max(result, i - j + 1);
            }
        }
        return result;
    }
};