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

int n, m, q;

void print_chip(int**);

void shift_col(int** chip, int c) {
    int tmp1 = chip[0][c], tmp2;
    for(int i = 1; i < n; i++) {
        tmp2 = chip[i][c];
        chip[i][c] = tmp1;
        tmp1 = tmp2;

    }
    chip[0][c] = tmp1;
    // print_chip(chip);
}

void shift_row(int** chip, int r) {
    int tmp1 = chip[r][0], tmp2;
    for (int i = 1; i < m; i++) {
        tmp2 = chip[r][i];
        chip[r][i] = tmp1;
        tmp1 = tmp2;
    }
    chip[r][0] = tmp1;
    // print_chip(chip);
}

void print_chip(int** chip) {

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (j < m - 1) cout << chip[i][j] << " ";
            else cout << chip[i][j];
        }
        cout << endl;
    }
}

int main() {
    cin >> n >> m >> q;
    string token;
    vector<string> ins;
    int** chip = (int** ) malloc(sizeof(int*) * n);

    for (int i = 0; i < n; i++) {
        chip[i] = (int*) malloc(sizeof(int) * m);
        for (int j = 0; j < m; j++) {
            chip[i][j] = 0;
        }
    }


    for (int i = 0; i < q; i++) {
        string ini;
        cin >> token;
        ini += token;
        if (token[0] == '1' || token[0] == '2') {cin >> token; ini += token;}
        else {cin >> token; ini += token; cin >> token; ini += token; cin >> token; ini += token;}
        ins.push_back(ini);
    }

    for (int i = 0; i < q; i++) {
        string ini = ins.back();
        // cout << "Ins: " << ini<< endl;
        ins.pop_back();
        if (ini[0] == '1') {
            shift_row(chip, ini[1] - '0' - 1);
        }
        else if (ini[0] == '2') {
            shift_col(chip, ini[1] - '0' - 1);
        }
        else {
            chip[ini[1] - '0'- 1][ini[2] -'0' - 1] = ini[3] - '0';
            // print_chip(chip);
        }

    }
    print_chip(chip);
    free(chip);
    return 0;
}
