/*
ID: minh.fo1
LANG: C++
TASK: ride
*/

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string isGo(string s1, string s2) {
    long p1 = 1, p2 = 1;
    for (int i = 0; i < s1.size(); ++i)
        p1 *= (s1.at(i) - 64);
    
    for (int i = 0; i < s2.size(); ++i)
        p2 *= (s2.at(i) - 64);
    
    if (p1 % 47 == p2 % 47)
        return "GO";
    else
        return "STAY";
}

int main() {
    ofstream fout ("ride.out");
    ifstream fin ("ride.in");
    string cometName, grName;
    fin >> cometName; fin >> grName;
    fout << isGo(cometName, grName) << endl;
    
    return 0;
}