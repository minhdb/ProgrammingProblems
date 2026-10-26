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
#include <cstring>
#define FOR(x, y) for (int x = 0; x < y; x++)

/*
 * TopCoder SRM 209 Div 1 Level 1 - MedalTable
 * Minh Bui
 */
 
using namespace std;

class MedalTable {
public:
	vector <string> generate(vector <string>);
    static bool compare(const pair<string, int*> &i, const pair<string, int*> &j) {  
        if (i.second[0] < j.second[0]) return false;
        else if (i.second[0] == j.second[0]) {
            if (i.second[1] < j.second[1]) return false;
            else if (i.second[1] == j.second[1]) {
                if (i.second[2] < j.second[2]) return false;
                else if (i.second[2] == j.second[2]) return i.first < j.first;
                else return true;
            } else return true;
        } else return true;	
    }
};

vector <string> MedalTable::generate(vector <string> results) {
    map <string, int*> table;
    
    FOR(i, (results.size())) {
        istringstream c(results[i]);
        int j = 0; string n;
        while (c >> n) {
            map <string, int*>::iterator it = table.find(n);
            if (it == table.end()) {
                table[n] = new int[3];
                FOR(k, 3) table[n][k] = 0;
            }
            
            if (j == 0) table[n][0]++;
            else if (j == 1) table[n][1]++;
            else table[n][2]++;
            j++;
        }
    }
    vector< pair <string, int*> > v(table.size());
    copy(table.begin(), table.end(), v.begin());
    sort(v.begin(), v.end(), compare);
    
    vector<string> r;
    FOR(i, (v.size())) {
        string s = v[i].first + " " + to_string(v[i].second[0]) 
            + " " + to_string(v[i].second[1]) 
            + " " + to_string(v[i].second[2]);
        r.push_back(s);
    }
    return r;
}
