/*
ID: minh.fo1
PROG: palsquare
LANG: C++11
*/

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
#include <fstream>
#define vi vector<int>
#define vii vector< vector <int> >
#define FOR(x, size) for(int x = 0; x < size; ++x)

/* Problem: USACO palsquare
 * Minh Bui
 */

using namespace std;

char map_system[21] = {'0', '1', '2', '3', '4', '5', 
    '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E',
    'F', 'G', 'H', 'I', 'J'};

bool checkPal(string s) {
    int i = 0, j = s.size() - 1;
    while (i < j) {
        if (s[i] != s[j]) return false;
        i++; j--;
    }
    return true;
}

string tenToB(string s, int b) {
    string result = "";
    int n = stoi(s);
    while (n != 0) {
        result += map_system[n % b];
        n /= b;
    }
    reverse(result.begin(), result.end());
    return result;
}

int main() {
    int b; bool baseTen;
    string s;
    ifstream fin("palsquare.in");
    ofstream fout("palsquare.out");
    fin >> b;
    if (b == 10) {
        for (int i = 1; i <= 300; i++) {
            s = to_string(i * i);
            if (checkPal(s)) fout << i << " " << s << endl;
        }
    } else {
        for (int i = 1; i <= 300; i++) {
            s = tenToB(to_string(i * i), b);
            if (checkPal(s)) fout << tenToB(to_string(i), b) << " " << s << endl;
        }
    }
    return 0;
}
