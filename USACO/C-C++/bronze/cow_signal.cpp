/**
 * USACO The Cow-Signal
 * https://usaco.org/index.php?page=viewproblem2&cpid=665
 * Bessie and her cow friends are playing as their favorite cow superheroes. Of
 * course, everyone knows that any self-respecting superhero needs a signal to
 * call them to action. Bessie has drawn a special signal on a sheet of M×N
 * paper (1≤M≤10,1≤N≤10), but this is too small, much too small! Bessie wants
 * to amplify the signal so it is exactly K times bigger (1≤K≤10) in each
 * direction. The signal will consist only of the '.' and 'X' characters.
 *
 * INPUT FORMAT (file cowsignal.in):
 * The first line of input contains M, N, and K, separated by spaces. The next
 * M lines each contain a length-N string, collectively describing the picture
 * of the signal.
 *
 * OUTPUT FORMAT (file cowsignal.out):
 * You should output KM lines, each with KN characters, giving a picture of the
 * enlarged signal.
 *
 * SAMPLE INPUT:
 * 5 4 2
 * XXX.
 * X..X
 * XXX.
 * X..X
 * XXX.
 *
 * SAMPLE OUTPUT:
 * XXXXXX..
 * XXXXXX..
 * XX....XX
 * XX....XX
 * XXXXXX..
 * XXXXXX..
 * XX....XX
 * XX....XX
 * XXXXXX..
 * XXXXXX..
 */
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int main()
{
    int m,n,k;
    ifstream fin("cowsignal.in");
    ofstream fout("cowsignal.out");
    fin >> m >> n >> k;
    vector<string> in;
    in.reserve(m);
    vector<string> out;
    out.reserve(k*m);

    for (auto i = 0; i < k * m; i++) {
        string cur_out_line(k*n, 'x');
        out.push_back(cur_out_line);
    }

    for (auto i = 0; i < m; i++) {
        string cur_line;
        fin >> cur_line;
        in.push_back(cur_line);
    }

    for (const auto& r : out)
        fout << r << "\n";
    return 0;
}
