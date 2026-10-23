// Convert h to scale of 0 - 11
// Convert m and s to scale of 0 - 11
// Consider h, m, and s each.
// Return "NO" iff:
// 1. If t1 < t2:
//  - There's at least h, or m, or s between t1 -> t2.
//  - There's at least h, or m, or s between t2 -> 0 and there's at least h, or m, or s between 0 -> t1.
//
// 2. If t2 < t1:
//  - There's at least h, or m, or s between t1 -> 0 and there's at least h, or m, or s between 0 -> t2.
//  - There's at least h, or m, or s between t2 -> t1.
//

#include <iostream>

using namespace std;

bool is_possible(int t1, int t2, int h, double m, double s) {
    int t1_to_s = t1 * 60 * 60;
    int t2_to_s = t2 * 60 * 60;

    int hour_marker = h * 60 * 60;
    int min_marker = m * 60;
}

int main()
{
    int h,m,s,t1,t2;
    cin >> h >> m >> s >> t1 >> t2;

    if (is_possible(t1, t2, h, m, s))
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
    return 0;
}
