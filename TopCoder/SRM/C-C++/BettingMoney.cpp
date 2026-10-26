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
 * Problem: SRM191 Round 1 - Div II - Level 1
 * Minh Bui
 */

using namespace std;

class BettingMoney {
    public:
        int moneyMade(vector<int> amounts, vector<int> centsPerDollar, int finalResult) {
            int netGain = 0;
            for (int i = 0; i < amounts.size(); i++) {
                if (i == finalResult)
                    netGain -= (centsPerDollar[finalResult] * amounts[finalResult]);
                else
                	netGain += amounts[i] * 100;
            }
            
            return netGain;
        }
};

int main() {
    return 0;
}
