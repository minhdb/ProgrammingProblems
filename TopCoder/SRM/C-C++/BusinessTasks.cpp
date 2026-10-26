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

/*
 * TopCoder SRM236 Div 1 Level 1.
 * Minh Bui
 */

class BusinessTasks {
public:
	string getTask(vector <string> list , int n) {
		int c = -1;
		while (list.size() != 1) {
			for (int i = 0; i < n; i++) {
				c++;
				if (c >= list.size()) c = 0;
			}
			list.erase(list.begin() + c);
			c--;
		}
		return list[0];
	}
};

