/*
ID: minh.fo1
PROG: namenum
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

/* Problem: USACO namenum
 * Minh Bui
 */

using namespace std;

/* Bruteforce solution-out of memory
char* arr[10];
stack<string> s;

vector<string> findNames(vector<string> &words, string &num) {
    int n = num.size();
    //stack<string> s;
    vector<string> availNames;
    map <string, bool> visited;
    string na = "";
    for (int i = 0; i < 3; i++) {
        s.push(na + arr[num[0] - '0'][i]);
    }
    while (!s.empty()) {
        string cur = s.top();
        s.pop();
        if (cur.size() == n) {
            if (binary_search(words.begin(), words.end(), cur))
                availNames.push_back(cur);
        } else {
            //cout << cur << endl;
            string push_s = cur;
            for (int j = 0; j < 3; j++) {
                push_s = cur + arr[num[cur.size()] - '0'][j];
                if (!visited[push_s]) {
                    visited[push_s] = true;
                    s.push(push_s);
                }
            }
        }
    }
    return availNames;
}
*/

int arr[26];

int main() {
    string num, s;
    vector<string> words;
    ifstream fin ("namenum.in");
    ofstream fout("namenum.out");
    ifstream dict ("dict.txt");

    fin >> num;
    while (dict >> s) {
        if (s.find('Q') == -1 && s.find('Z') == -1)
            words.push_back(s);
    }
    /*
     * Brute-force solution.
     * Out of memory.
    char c = 'A';
    for (int i = 2; i < 10; i++) {
        arr[i] = new char[3];
        for (int j = 0; j < 3; j++) {
            if (c == 'Q') c++;
            arr[i][j] = c;
            c++;
        }
    }
    int n = num.size();

    vector<string> names = findNames(words, num);
    if (names.size()) {
        sort(names.begin(), names.end());
        for (int i = 0; i < names.size(); i++)
            fout << names[i] << endl;
    } else
        fout << "NONE" << endl;
    */
    int change = 0;
    int init = 2;
    for (int i = 0; i < 26; i++) {
        if (i + 'A' != 'Q' && i + 'A' != 'Z') {
            if (change == 3) {
                init++;
                change = 0;
            }
            arr[i] = init;
            change++;
        } else arr[i] = 0;
    }

    vector<string> names;
    vector<string> possible;

    for (int i = 0; i < words.size(); i++) {
        string build = "";
        for (int j = 0; j < words[i].size(); j++) {
            build += to_string(arr[words[i][j] - 'A']);
        }
        if (build == num) possible.push_back(words[i]);
    }

    if (possible.size()) {
        for (int i = 0; i < possible.size(); i++) {
            fout << possible[i] << endl;
        }
    } else fout << "NONE" << endl;
    return 0;
}
