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
 * Problem: SRM 147 Div II Level 1
 * CCipher TopCoder
 * Minh Bui
 */

using namespace std;

class CCipher {
    public:
        string decode(string cipherText, int shift) {
            string newS = "";
            for (size_t i = 0; i < cipherText.size(); i++) {
                char c = (((cipherText[i] - 'A' - shift) % 26) + 26) % 26 + 'A';
                newS += c;
            }
            return newS;
        }
};