#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main()
{
    ifstream fin("teleport.in");
    ofstream fout("teleport.out");

    int a,b,x,y;
    fin >> a >> b >> x >> y;
    fout << min({abs(a-b), abs(x-a) + abs(y-b), abs(y-a) + abs(x-b)}) << "\n";
    return 0;
}
