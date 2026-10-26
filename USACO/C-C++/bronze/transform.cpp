/*
ID: minh.fo1
PROB: transform
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

/* Problem: transform
 * Minh Bui
 */

using namespace std;

vector<string> rotate1(vector<string> &pattern) {
    vector<string> result = pattern;
    int n = pattern.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = pattern[n-j-1][i];
        }
    }
    return result;
}

vector<string> rotate2(vector<string> pattern) {
    vector<string> result = rotate1(pattern);
    return rotate1(result);
}

vector<string> rotate3(vector<string> &pattern) {
    vector<string> result = rotate2(pattern);
    return rotate1(result);
}

vector<string> reflect(vector<string> &pattern) {
    vector<string> result = pattern;
    int n = pattern.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = pattern[i][n-j-1];
        }
    }
    return result;
}

int solve(vector<string> &pattern, vector<string> &final) {
    vector<string> toy = reflect(pattern);
    if (rotate1(pattern) == final) return 1;
    else if (rotate2(pattern) == final) return 2;
    else if (rotate3(pattern) == final) return 3;
    else if (toy == final) return 4;
    else if (rotate1(toy) == final ||
            rotate2(toy) == final ||
            rotate3(toy) == final) return 5;
    else if (pattern == final) return 6;
    else return 7;
}

int main() {
    ifstream fin  ("transform.in");
    ofstream fout ("transform.out");
    int n; string row;
    fin >> n;
    vector<string> pattern(n);
    vector<string> final(n);
    for (int i = 0; i < n; i++) {
        fin >> pattern[i];
    }

    for (int i = 0; i < n; i++) {
        fin >> final[i];
    }
    fout << solve(pattern, final) << endl;

    return 0;
}
