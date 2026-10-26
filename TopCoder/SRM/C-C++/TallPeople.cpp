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
#define FOR(x, y) for (int x = 0; x < y; x++)

/*
 * TopCoder SRM 208 Div 1 Level 1 - TallPeople
 * Minh Bui
 */

using namespace std;

class TallPeople {
public:
	vector <int> getPeople(vector <string>);
    int getEst(vector <int>, bool);
};

vector <int> TallPeople::getPeople(vector <string> people) {
	vector< vector <int> > g (people.size());
    FOR(i, (people.size())) {
        istringstream c (people[i]);
        int h = 0;
        while (c >> h) { g[i].push_back(h); }
    }
    
    vector<int> result (2);
    vector<int> shortest;
    vector<int> tallest;
    FOR(i, (people.size())) shortest.push_back(getEst(g[i], false));
    result[0] = getEst(shortest, true);
    
    vector< vector <int> > g_trans (g[0].size());
    FOR(i, (people.size())) {
        FOR(j, (g[0].size()))
            g_trans[j].push_back(g[i][j]);
            
    }
    
    FOR(i, (g[0].size())) tallest.push_back(getEst(g_trans[i], true));
    result[1] = getEst(tallest, false);
    return result;    
}

int TallPeople::getEst(vector<int> people, bool tallest) {
    int result = people[0];
    for (int i = 1; i < people.size(); i++) {
        if (tallest) {
            if (result < people[i]) result = people[i];
        } else
            if (result > people[i]) result = people[i];
    }
    return result;
}

<%:testing-code%>
// Powered by [KawigiEdit] 2.0!
