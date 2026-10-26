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
 * TopCoder SRM 223 Div I Level 3
 * Minh Bui
 */
 
 class RevolvingDoors {
    public:
        int turns(vector<string>);
        vector<string> bfsState(int*, vector<string>);
 }

int RevolvingDoors::turns(vector<string> map) {
    return 0;
}

vector<string> RevolvingDoors::bfsState(int* start, vector<string> state) {
    vector<string> newState = state;
    bool visited[state.size()][state.size()];
    
    for (int i = 0; i < state.size(); i++) {
        for (int j = 0; j < state.size(); j++)
            if (newState[i][j] == ' ' || 
                newState[i][j] == '|' ||
                newState[i][j] == '-') visited[i][j] = false;
    }
    
    fill[start[0]][start[1]] = true;
    queue<int*> qu;
    qu.push();
    
    while(!q.empty()) {
        int* q = qu.front();
        qu.pop();
        
        vector<int*> availGrids = availGrid(q, state);
        for (int i = 0; i < availGrids.size(); i++) {
            int* node = availGrids[i];
            if (!fill[node[0]][node[1]]) {
                
            }
        }
    }    
    return newState;
}

vector<int*> RevolvingDoors::availGrid(int* start, vector<string> state) {
    vector<int*> avail;
    for (int i = -1; i >= 1; i += 2) {
        for (int j = -1;; j >= 1; j += 2) {
            int* nState = new int();
            nState[0] = start[0] + i;
            nState[1] = start[1] + j;
            if (state[nState[0]][nState[1]] == "#") continue;
            else {
                if ((state[nState[0]][nState[1]] == "-" && 
                     (nState[1] - 1 == start[1] || nState[1] + 1 == start[1])) ||
                    (state[nState[0]][nState[1]] == "|" && 
                     (nState[0] - 1 == start[0] || nState[0] + 1 == start[0])) ||
                    (state[nState[0]][nState[1]] == ' ')
                        avail.push_back(nState);
            }
        }
    }
    return avail;
}