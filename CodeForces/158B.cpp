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
 * Problem: 158B.
 * Minh Bui
 */

using namespace std;

int bin_search(vector<unsigned int> a, unsigned int v) {
    if (a.empty()) return -1;

    int low = 0;
    int high = a.size();

    while (low <= high) {
        int mid = (low + high) / 2;
        if (v == a[mid]) return mid;
        else if (v < a[mid]) high = mid - 1;
        else low = mid + 1;
    }

    return -1;
}

int main() {
    unsigned int n, s, i, c;
    c = i = 0; vector<unsigned int> students;
    cin >> n;
    while(n--) {
        cin >> s;
        students.push_back(s);
    }
    n = students.size();
    sort(students.begin(), students.end());
    while (!students.empty()) {
        c++;
        s = students.back();
        students.pop_back();
        int d = 4 - s;
        int sum = d;
        while(!students.empty() && d > 0 && sum > 0) {
            int f = bin_search(students, d);
            if (f != -1)
            {
                sum -= students[f];
                students.erase(students.begin() + f);
            } else 
                d--;
        }
    }
    cout << c << endl;
    return 0;
}

