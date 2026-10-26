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
 * Problem: SRM146 Div II - Level 1
 * YahtzeeScore
 * Minh Bui
 */

using namespace std;

class YahtzeeScore {
    public:
        int maxPoints(vector<int> toss) {
            int arr[6];
            memset(arr, 0, sizeof(int) * 6);
            for (int i = 0; i < toss.size(); i++) {
                arr[toss[i] - 1]++;
            }

            int m = 0;
            for (int i = 0; i < 6; i++) {
                m = max(m, (i + 1) * arr[i]); 
            }
            return m;
        }
};

int main() {
    return 0;
}
