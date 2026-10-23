#include <fstream>
using namespace std;

int main()
{
    ifstream fin("paint.in");
    ofstream fout("paint.out");

    int a,b,c,d;
    fin >> a >> b >> c >> d;
    if ((b < c) || (d < a)) {
        fout << (b-a) + (d-c) << "\n";
    } else {
        fout << max(d,b) - min(a,c) << "\n";
    }
    return 0;
}
