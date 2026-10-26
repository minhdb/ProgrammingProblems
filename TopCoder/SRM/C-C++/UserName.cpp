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
#include <string>

/*
 * SRM 203 Div 2 level 1.
 * Minh Bui
 */

using namespace std;

class UserName {
public:
	string newMember(vector <string> existingNames, string newName) {
		string name = newName;
		int i = 1;
		while(find(existingNames, name)) { name = newName + to_string (i); i++; }
		return name;
	}
	
	bool find(vector <string> existingNames, string query) {
		for (int i = 0; i < existingNames.size(); i++) {
			if (query == existingNames[i])
				return true;
		}
		return false;
	}
};


<%:testing-code%>
// Powered by [KawigiEdit] 2.0!