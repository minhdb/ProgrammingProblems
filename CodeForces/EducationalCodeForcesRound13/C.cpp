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
#define vi vector<int>
#define vii vector< vector <int> >
#define FOR(x, size) for(int x = 0; x < size; ++x)

/*
 * Problem:
 * Minh Bui
 */

using namespace std;

int main() {
    long long n, a, b, p, q;
    cin >> n >> a >> b >> p >> q;
    long long ca = n / a;
    long long cb = n / b;
    long long cab = 0;
    if (a % b == 0 && a != b) {
        cb -= ca;
    } else if (b % a == 0 && a != b) {
        ca -= cb;
    } else {
        cab = n / (a*b);
        ca -= cab;
        cb -= cab;
    }
    long long r = 0;
    cout << ca << " " << cb << " " << cab << endl;
    r = ca*p + cb*q;
    p > q ? r += p*cab : r += q*cab;
    cout << r << endl;
    return 0;
}
