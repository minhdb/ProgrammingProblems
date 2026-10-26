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
 * Problem: Codeforces 237A
 * Minh Bui
 */

using namespace std;

int main() {
    int n, in, count = 0;
    cin >> n;
    queue<int> q;
    int last = 0, cur = 0;
    while(n--) {
        cin >> cur; cur *= 60;
        cin >> in; cur += in;
        if (q.empty()) q.push(cur);
        else {
            int temp = q.front();
            while(cur - temp >= 1 && !q.empty()) {
                q.pop();
                temp = q.front();
            }
            q.push(cur);
        }
        count = max(count, (int)q.size());
    }
    cout << count << endl;
    return 0;
}
