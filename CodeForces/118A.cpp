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
#define vi vector<int>
#define vii vector< vector <int> >
#define FOR(x, size) for(int x = 0; x < size; ++x)

/*
 * Problem: CodeForce 118A
 * Minh Bui
 */

using namespace std;

int main() {
    string s;
    cin >> s;
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == 'a' ||
            s[i] == 'o' ||
            s[i] == 'y' ||
            s[i] == 'e' ||
            s[i] == 'u' ||
            s[i] == 'i' )
        {
            s.erase (s.begin() + i); 
            i--;
        }
        else {
            s.insert(s.begin() + i, '.');
            i++;
        }
    }

    cout << s << endl;
    return 0;
}
