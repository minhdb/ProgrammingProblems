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
#include <queue>

using namespace std;

/*
 * TopCoder SRM 233 Div 1 Level 2
 * Minh Bui
 */

class SmartWordToy {
public:
	int minPresses(string, string, vector <string> );
};

int SmartWordToy::minPresses(string start, string finish, vector<string> forbid) {
    map< string, pair <int, string> > graph;
    
    graph[start] = make_pair(0, NULL);
    queue<string> q;
    q.push(start);
    
    while (!q.empty())
    {
        string cur = q.front();
        q.pop();
        // cout << "String: " << cur << " is dequed." << endl;
        for (int i = 0; i < cur.size(); i++) {
            for (int j = 1; j >= -1; j -= 2) {
                // State listing
                string curcopy = cur;
                if (curcopy[i] == 'a' && j == -1) curcopy[i] = 'z';
                else if (curcopy[i] == 'z' && j == 1) curcopy[i] = 'a';
                else curcopy[i] += j;
                
                // cout << curcopy << endl;
                for (int i = 0; i < forbid.size(); i++) {
                    istringstream c( forbid[i] );
                    string s; vector<string> fb;
                    while (c >> s) {fb.push_back(s);}
                    
                    if (fb[0].find_first_of(curcopy[0]) != -1 &&
                       fb[1].find_first_of(curcopy[1]) != -1 &&
                       fb[2].find_first_of(curcopy[2]) != -1 &&
                       fb[3].find_first_of(curcopy[3]) != -1) 
                    {
                        graph[curcopy] = make_pair(-1, cur);
                        // cout << "String: " << curcopy << " is not pushed.\n";
                        break;
                    }
                }
                
                if (graph.find(curcopy) == graph.end()) {
                    if (curcopy == finish) return graph[cur].first + 1;
                    graph[curcopy] = make_pair(graph[cur].first + 1, cur);
                    // cout << "String: " << curcopy << " is pushed.\n";
                    q.push(curcopy);
                } 
            }      
        }
    }
    return -1;
}


int main() {
    string start = "aaaa";
    string finish = "zzzz";
    vector<string> forbid;
    forbid.push_back("a a a z");
    forbid.push_back("a a z a");
    forbid.push_back("a z a a");
    forbid.push_back("z a a a");
    forbid.push_back("a z z z");
    forbid.push_back("z a z z");
    forbid.push_back("z z a z");
    forbid.push_back("z z z a");
    SmartWordToy *obj = new SmartWordToy();
    cout << obj->minPresses(start, finish, forbid) << endl;
    return 0;
}
