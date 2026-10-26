/**
 * Playing around with binary_search C++ STL.
 */

#include <algorithm>
#include <cstdio>
#include <vector>

using std::vector;
using std::binary_search;
using std::find;
using std::lower_bound;
using std::upper_bound;

/**
 * upper_bound returns an iterator to an element that's greater than the target.
 * lower_bound returns an iterator to an element that's greater than or
 * equal the target.
 */
int main()
{
    vector<int> A{1, 2, 4, 5, 6};
    printf("upper_bound of 3: %d\n", *upper_bound(A.begin(), A.end(), 3));
    printf("lower_bound of 3: %d\n", *lower_bound(A.begin(), A.end(), 3));
    return 0;
}
