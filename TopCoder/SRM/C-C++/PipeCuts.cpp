#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

/*
 * TopCoder SRM 233 Div II level 2.
 * Minh Bui
 */

using namespace std;

class PipeCuts {
public:
	double probability(vector <int>, int);
};

double PipeCuts::probability(vector <int> weldLocations, int L) {
    sort(weldLocations.begin(), weldLocations.end());
    double sum = 0, tests = 0;
    for (int i = 0; i < weldLocations.size(); i++)
        for (int j = 0; j < weldLocations.size(); j++) {
            tests++;
            if (weldLocations[i] > L ||
               weldLocations[j] - weldLocations[i] > L ||
               100 - weldLocations[j] > L) sum++
        }
    return sum / tests;
}

int main() {
    PipeCuts* obj = new PipeCuts();
    vector<int> pipe;
    pipe.push_back(25);
    pipe.push_back(50);
    pipe.push_back(75);
    cout << "Overall p: " << obj->probability(pipe, 50) << endl;
    return 0;
}


// Powered by [KawigiEdit] 2.0!