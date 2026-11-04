/**
 * C. Counting Rectangles Time limit per test: 1 second Memory limit per test:
 * 256 MB
 *
 * Alice likes geometric objects, in particular rectangles. Today she drew a
 * grid on a piece of paper, consisting of n horizontal and m vertical lines.
 * Since rectangles are her favorite shapes, she wants to know the number of
 * distinct rectangles on the grid that fulfill the following conditions:
 *
 * the rectangle is non-degenerate the sides must be either horizontal or
 * vertical the sides must lie on a grid line Two rectangles are identical if
 * and only if all corners between them coincide. Can you help her?
 *
 * Input
 * A line containing two integers n –number of horizontal lines and m –number of
 * vertical lines (1≤n,m≤100).
 *
 * Output
 * Print one integer – the number of distinct rectangles which fulfill the
 * conditions.
 *
 * Example
 *
 * Input
 * 3 4
 *
 * Output
 * 18
 */

#include <iostream>
using namespace std;
int main()
{
    int n, m;
    cin >> n >> m;
    long long rects_count = 0;
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            rects_count += (n - i) * (m - j);
        }
    }
    cout << rects_count << endl;
    return 0;
}
