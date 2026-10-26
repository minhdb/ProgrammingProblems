/**
 * The Daily Byte
 *
 * 07/21/2021
 *
 * You are transporting bricks on a construction site and want to work as
 * efficiently as possible. The weight of each brick is given by bricks[i].
 * Give na wheelbarrow that can carry up to (not including) 5000 lbs,
 * return the maximum number of bricks you can place in your wheelbarrow
 * to transport.
 *
 *
 * LeetCode equivalent: LC1196
 */

#include <vector>
#include <cassert>
#include <algorithm>

using std::vector;

/**
 * First solution that comes to my mind is that we can sort the bricks from
 * lightest to heaviest, and we always want to pick the lightest bricks.
 *
 * Is it correct?
 *
 * The time complexity: O(nlogn) due to sorting.
 */
size_t maxBricksSorting(vector<int>& bricks)
{
    size_t i = 0, total_weight = 0;
    std::sort(bricks.begin(), bricks.end());
    while (i < bricks.size() && total_weight < 5000)
        total_weight += bricks[i];

    if (total_weight >= 5000) return i - 1;
    else return i;
}

int main()
{

    vector<int> tc1{100,200,150,1000};
    size_t tc1_res = 4;
    assert(maxBricksSorting(tc1) == tc1_res);

    vector<int> tc2{900,950,800,1000,700,800};
    size_t tc2_res = 5;
    assert(maxBricksSorting(tc2) == tc2_res);
    return 0;
}
