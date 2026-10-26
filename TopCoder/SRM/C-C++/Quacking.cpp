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
#include <queue>

using namespace std;

/*
 * TopCoder SRM 687 Div 2.
 * Minh Bui
 */

class Quacking {
public:
	int quack(string);
};

int Quacking::quack(string s) {
	if (s.size() % 5 != 0) return -1;
	else {
		vector < pair <string, char> > q;
		queue < pair <string, char> > job;
		int count = 0;
		
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == 'q') {
				q.push_back(make_pair("q", 'u'));
				if (job.empty()) {count++;}
				else job.pop();
			}
			else {
				for (int j = 0; j < q.size(); j++) {
					if (s[i] == q[j].second) {
						q[j].first += to_string(s[i]);
						if (s[i] == 'u') q[j].second = 'a';
						else if (s[i] == 'a') q[j].second = 'c';
						else if (s[i] == 'c') q[j].second = 'k';
						else {
							job.push(q[j]);
							q.erase(q.begin() + j);
						}
					}
				}
			}
		}
		if (!q.empty()) return -1;

		else return count;
	}
}


// Powered by [KawigiEdit] 2.0!