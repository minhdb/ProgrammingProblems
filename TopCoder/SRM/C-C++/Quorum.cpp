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

using namespace std;

/**
 * Problem: TopCoder SRM 687 Div2
 * Minh Bui
 */

class Quorum {
public:
	int count(vector <int>, int);
};

int Quorum::count(vector <int> arr, int k) {
	sort(arr.begin(), arr.end());
	int sum = 0;
	for (int i = 0; i < k; i++) sum += arr[i];
	return sum;
}


// Powered by [KawigiEdit] 2.0!