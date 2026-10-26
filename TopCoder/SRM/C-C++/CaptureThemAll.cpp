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
 * TopCoder SRM 207 Dev II Level 3
 * Minh Bui
 */

class CaptureThemAll {
    public:
        int fastKnight(string, string, string);
        int bfs(int*, int*);
        vector<int*> generatePossibleStates(int*); 
};

int CaptureThemAll::fastKnight(string knight, string rook, string queen) {
    int start[] = {knight[0] - 97, knight[1] - '0' - 1};
    int rk[] = {rook[0] - 97, rook[1] - '0' - 1};
    int qn[] = {queen[0] - 97, queen[1] - '0' - 1};

    int sr = bfs(start, rk);
    int sq = bfs(start, qn);
    int rq = bfs(rk, qn);    

    int p1 = sr + rq;
    int p2 = sq + rq;
    int p3 = 2 * sq + sr;
    int p4 = 2 * sr + sq;
    vector<int> listPaths;
    listPaths.push_back(p1);
    listPaths.push_back(p2);
    listPaths.push_back(p3);
    listPaths.push_back(p4);

    int min = p1;
    for (int i = 1; i < listPaths.size(); i++)
        if (min > listPaths[i]) min = listPaths[i];
    
    return min;
}

int CaptureThemAll::bfs(int* start, int* finish) {
    int board[8][8];
    
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) board[i][j] = -1;
    
    board[start[0]][start[1]] = 0;
    
    queue<int*> q;
    q.push(start);
    
    while(!q.empty()) {
        int* cur = q.front();
        q.pop();
        
        vector<int*> possibleStates = generatePossibleStates(cur);
        for (int i = 0; i < possibleStates.size(); i++) {
            int* nxtState = possibleStates[i];
            if (board[nxtState[0]][nxtState[1]] == -1)
            {
                board[nxtState[0]][nxtState[1]] = board[cur[0]][cur[1]] + 1;
                if (nxtState[0] == finish[0] &&
                   nxtState[1] == finish[1]) return board[nxtState[0]][nxtState[1]];
                q.push(possibleStates[i]);
            }
        }
    }
    
    return -1;
}

vector<int*> CaptureThemAll::generatePossibleStates(int* start) {
    vector<int*> states;
    for (int i = -2; i <= 2; i += 4) {
        for (int j = -1; j <= 1; j += 2) {
            if (start[0] + i >= 0 && start[0] + i < 8 &&
                start[1] + j >= 0 && start[1] + j < 8) {
                int* state = new int();
                state[0] = start[0] + i;
                state[1] = start[1] + j;
                
                states.push_back(state);
            }
            
            if (start[0] + j >= 0 && start[0] + j < 8 &&
               start[1] + i >= 0 && start[1] + i < 8) {
                int* state = new int();
                state[0] = start[0] + j;
                state[1] = start[1] + i;
                states.push_back(state);
            }
        }
    }
    
    // cout << "Possible state of " << start[0] << ", " << start[1] << endl;
    // for (int i = 0; i < states.size(); i++) {
    //    cout << states[i][0] << " " << states[i][1] << endl;
    // }
    return states;
}

int main() {
    string knight = "a1";
    string rook = "b3";
    string queen = "c5";
    CaptureThemAll *obj = new CaptureThemAll();
    cout << obj->fastKnight(knight, rook, queen) << endl;
    
    return 0;
}