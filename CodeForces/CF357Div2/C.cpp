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
#include <cstring>
#include <queue>
#define vi vector<int>
#define vii vector< vector <int> >
#define FOR(x, size) for(int x = 0; x < size; ++x)

/*
 * Problem:
 * Minh Bui
 */

using namespace std;

int main() {
    int n, r, in;
    string a;
    cin >> n;
    r = 0;
    priority_queue<int> q;
    vector< pair <string, int> > ins;
    vector< pair <string, int> > rec;
    while(n--) {
        cin >> a;
        if (a != "removeMin") {
            cin >> in;
            ins.push_back(make_pair(a, in));
        }
        else
            ins.push_back(make_pair(a, 0));
    }
    
    while(!ins.empty()) {
        pair<string, int> cur = ins.front();
        ins.erase(ins.begin());
        
        string instruction = cur.first;
        int v = cur.second;
        
        if (instruction == "getMin") {
            while(!q.empty() && q.top() < v) {  
                q.pop();
                rec.push_back(make_pair("removeMin", 0));
            }
            if (q.empty() || q.top() != v) {
                q.push(v);
                rec.push_back(make_pair("insert", v));  
                r++;
            }
            rec.push_back(cur);
            r++;
        } else if (instruction == "removeMin") {
            int value;
            if (!q.empty()) {
                q.pop();
            } else {
                q.push(0);
                rec.push_back(make_pair("insert", 0));
                q.pop();
                r++;
            }
            rec.push_back(cur);            
        } else if (instruction == "insert") {
            q.push(v);
            rec.push_back(cur);
            r++;
        }
    }
    cout << rec.size() << endl;
    for (int i = 0; i < rec.size(); i++) {
        cout << rec[i].first;
        if (rec[i].first != "removeMin")
            cout <<" " << rec[i].second << endl;
        else cout << endl;
    }
    return 0;
}
