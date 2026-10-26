/*
ID: minh.fo1
LANG: C++11
TASK: gift1
*/

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

typedef struct Person {
    int init, n;
    int current;
} Person;

int main() {
    int init, np, n; string name;
    map<string, Person*> group;
    ifstream fin ("gift1.in");
    ofstream fout ("gift1.out");
    
    fin >> np;
    vector<string> arrayN(np);
    
    for (int i = 0; i < np; ++i) {
        fin >> name;
        arrayN[i] = name;
        group[name] = new Person;
        group[name]->init = 0;
        group[name]->current = 0;
    }
    
    for (int i = 0; i < np; ++i) {
        fin >> name >> init >> n;
        group[name]->n = n;
        group[name]->init = init;
        group[name]->current += group[name]->init;
        
        string rec;
        for (int j = 0; j < group[name]->n; ++j) {
            //cin >> rec;
            fin >> rec;
            if (group[name]->n != 0)
            {
                group[rec]->current += (group[name]->init / group[name]->n);
                group[name]->current -= (group[name]->init / group[name]->n);
            }
        }
    }
    
    for(auto b : arrayN) 
        fout << b << " " << (group[b])->current - (group[b])->init << endl;
        //cout << b->first << " " << (b->second)->current << endl;
    
    
    return 0;
    
}