/*
ID: minh.fo1
LANG: C++11
TASK: friday
*/

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() {
    int N, m, d, y, days[7], i;
    bool leap = false;
    ifstream fin ("friday.in");
    ofstream fout ("friday.out");
    
    days[0] = 1;
    for (i = 1; i < 7; i++)
        days[i] = 0;
    
    fin >> N;
    y = 1900; d = 0; m = 1;
    while (y < 1900 + N) {
        m = 1; leap = false;
        if (y % 100 != 0) { 
            if (y % 4 == 0) leap = true;
        } else if (y % 400 == 0) leap = true;
        
        while (m < 13) {
            if (m == 9 || m == 4 || m == 6 || m == 11) d = d + 30 % 7;
            else if (m == 2) {
                if (leap) d = d + 29 % 7;      
            } else d = d + 31 % 7;
            
            if (d > 6) d -=7;
            days[d]++;
            m++;
        }
        y++;
    }
    days[d]--;
    fout << days[0] << " " << days[1] << " " << days[2] << " " << days[3] << " " << days[4] << " " << days[5] << " " << days[6] << endl;
    return 0;
}