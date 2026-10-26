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
 * TopCoder SRM 678 Round 1 Division II - Level 1
 * Minh Bui
 */

using namespace std;

class ThePhantomMenace {
public:
	int find(vector <int>, vector <int>);
};

int ThePhantomMenace::find(vector <int> doors, vector <int> droids) {
	int max = 0;
	for (int i = 0; i < doors.size(); i++) {
		int minDist = 101;
		for (int j = 0; j < droids.size(); j++) {
			int dist = abs(droids[j] - doors[i]);
			if (dist < minDist) minDist = dist;
		}
		if (minDist > max) max = minDist;
	}
	return max;
}


// Powered by [KawigiEdit] 2.0!
