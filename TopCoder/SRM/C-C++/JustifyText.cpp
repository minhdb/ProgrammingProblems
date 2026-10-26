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
 * TopCoder SRM 233 Div II - Level 1.
 * Minh Bui
 */

using namespace std;

class JustifyText {
public:
	vector <string> format(vector <string>);
};

vector <string> JustifyText::format(vector <string> text) {
	int maxL = 0;
	for (int i = 0; i < text.size(); i++)
		if (text[i].size() > maxL) maxL = text[i].size();
		
	for (int i = 0; i < text.size(); i++) {
		if (text[i].size() < maxL)
			{
				int d = maxL - text[i].size();
				string spaces (d, ' ');
				text[i] = spaces + text[i];
			}
	}
	
	return text;
}

<%:testing-code%>
// Powered by [KawigiEdit] 2.0!