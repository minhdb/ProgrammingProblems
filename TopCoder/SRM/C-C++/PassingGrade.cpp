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
 * Problem: SRM185 Div II Level 1
 * TopCoder PassingGrade
 * Minh Bui
 */

using namespace std;

class PassingGrade {
    public:
        int pointsNeeded(vector<int> pointsEarned, vector<int> pointsPossible, int finalExam) {
            int earned = 0, all = 0, tfinal = 0;
            for (int n : pointsEarned) earned += n;
            for (int n : pointsPossible) all += n;
            all += finalExam;
            tfinal = ceil((0.65 * all) - earned);
            if (tfinal > finalExam)
                return -1;
            else if (tfinal < 0) return 0;
            else return tfinal;
        }
};

int main() {
    return 0;
}
