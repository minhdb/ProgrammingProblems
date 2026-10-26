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
 * Problem: UVA12250
 * Minh Bui
 */

using namespace std;

int main() {
    int c = 1;
    string s;
    while (cin >> s && s != "#") {
            if (s == "HELLO")
                cout << "Case " << c << ": ENGLISH" << endl;
            else if (s == "HOLA")
                cout << "Case " << c << ": SPANISH" << endl;
            else if (s == "HALLO")
                cout << "Case " << c << ": GERMAN" << endl;
            else if (s == "BONJOUR")
                cout << "Case " << c << ": FRENCH" << endl;
            else if (s == "CIAO")
                cout << "Case " << c << ": ITALIAN" << endl;
            else if (s == "ZDRAVSTVUJTE")
                cout << "Case " << c << ": RUSSIAN" << endl;
            else
                cout << "Case " << c << ": UNKNOWN" << endl;
        c++;
    }
    return 0;
}
