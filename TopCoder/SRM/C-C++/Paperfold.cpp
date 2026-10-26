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
 * Problem: SRM 162 Div I Level 1
 * Paperfold TopCoder
 * Minh Bui
 */

using namespace std;

class PaperFold {
    public:
        int numFolds(vector<int> paper, vector<int> box) {
            double box_dim = box[0] * box[1];
            double** g = new double*[5];
            for (int i = 0; i < 5; i++) {
                g[i] = new double[5];
            }
            double min_s;
            pair<int, int> min_ind = make_pair(5, 4);
            for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 5; j++) {
                    double w = paper[0], l = paper[1];
                    w /= pow(2, i);
                    l /= pow(2, j);
                    g[i][j] = w * l;
                    int min_fold = i + j;
                    if (min_fold < (min_ind.first + min_ind.second) && g[i][j] <= box_dim) {
                        min_ind = make_pair(i, j);
                        min_s = g[i][j];
                        cout << "w: " << w << " " << "l: " << l << endl;
                    }
                }
            }
            cout << min_ind.first << " " << min_ind.second << endl;
            cout << "paper: " << min_s << endl;
            cout << "box_dim: " << box_dim << endl;
            if (min_ind.first == 5) return -1;
            else return (min_ind.first + min_ind.second);
        }
};