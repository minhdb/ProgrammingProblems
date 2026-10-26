/**
 * USACO Promotion Counting
 * https://usaco.org/index.php?page=viewproblem2&cpid=591
 */

#include <fstream>

using namespace std;

int main()
{
    ifstream fin("promote.in");
    ofstream fout("promote.out");
    int a, b, c, d;
    int a_p, b_p, c_p, d_p;
    fin >> a >> a_p;
    fin >> b >> b_p;
    fin >> c >> c_p;
    fin >> d >> d_p;

    fout << b_p - b + c_p - c + d_p - d << "\n";
    fout << c_p - c + d_p - d << "\n";
    fout << d_p - d << "\n";

    return 0;
}
