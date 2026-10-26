/*
ID: minh.fo1
LANG: C++11
TASK: beads
*/

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

int main() {
    ifstream fin ("beads.in");
    ofstream fout ("beads.out");
    string beads; int n;
    
    fin >> n; fin >> beads;
    int left, right, max;
    max = 0;
    for (int i = 0; i < n; i++) {
        int count = 0;
        bool s = false;
        char curCol = 'w';
        for (int j = 0; j < n; j++) {
            char cur = beads[(i + j) % n];
            if (cur != 'w') {
                if (curCol == 'w') curCol = cur;
                else if (curCol != cur) {
                    if (s) break;
                    else {
                        curCol = cur;
                        s = true;
                    }
                } 
            }
            count++;
        }
        max = std::max(max, count);
    }
    
    fout << max << endl;
    return 0;
}