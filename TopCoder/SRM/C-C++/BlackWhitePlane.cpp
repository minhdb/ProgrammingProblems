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
#define FOR(x, size) for(int x = 0; x < size; ++x)
#define PI 3.141592653589793

/*
 * TopCoder - Single Round Match 271 Round 1 - Division II, Level Two
 * Minh Bui
 */

using namespace std;

class BlackWhitePlane {
    public:
    int x[64], y[64], r[64];
    double area(vector<string> circles) {
        double result, s; 
        result = 0;
        FOR(i, circles.size()) {
            istringstream s ( circles[i] );
            s >> x[i]; s >> y[i]; s >> r[i];
        }
    
    FOR(i, circles.size()) {
        s = r[i] * r[i] * PI;
        int containsMe = 0;
        FOR(j, circles.size()) {
            if (r[j] > r[i]) {
                if (contains(i, j)) containsMe++;
            }
        }
        
        if (containsMe % 2 == 1) s = -s;
        result += s;
    }
    return result;
}

    bool contains(int c, int q) {
        double d = sqrt ((x[c] - x[q]) * (x[c] - x[q]) + (y[c] - y[q]) * (y[c] - y[q]));
        if (d < r[q]) return true;
        else return false;
    }
};


int main() {
    // Test cases.
    BlackWhitePlane *object = new BlackWhitePlane();
    
    string t0[] = {"1 1 1"};
	vector <string> p0(t0, t0+sizeof(t0)/sizeof(string));
    
    string t1[] = {"4 3 1", "3 2 3", "8 1 1"};
	vector <string> p1(t1, t1+sizeof(t1)/sizeof(string));
    
    cout << object->area(p0) << endl;
    cout << object->area(p1) << endl;
    
    return 0;
}