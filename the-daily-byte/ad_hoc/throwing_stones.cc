/**
 * The Daily Byte
 *
 * 07/17/2021
 *
 * You are given a group of stones, all of which have a positive weight. At
 * each turn, we select the heaviest 2 stones and smash them together. When
 * smash these 2 stones together, one of 2 things can happen:
 *
 * 1. If the stones are both the same weight, both stones are destroyed.
 * 2. If the weights of the stones are not equal, the smaller of the two
 * stones is destroyed and the remaining stone's weight is updated to the
 * difference (i. e. if we smash 2 stones together of weight 3 and weight 4
 * the stone with weight 3 is destroyed and the stone with original weight 5
 * now has weight 2.)
 *
 * Equivalent: LC 1046.
 */

#include <vector>
#include <cassert>
#include <algorithm>
#include <cstdio>

using std::vector;
using std::swap;

int remove_largest(vector<int>& stones)
{
    int max_ele = stones[0];
    
    if (stones.size() != 1) {
        int max_idx = 0;
        for (size_t i = 1; i < stones.size(); i++) {
            if (max_ele < stones[i]) {
                max_idx = i;
                max_ele = stones[i];
            }
        }

        swap(stones[max_idx], stones[stones.size() - 1]);
    }

    stones.pop_back();
    return max_ele;
}

    //
    // 1. Search for the max and the 2nd max weight stones.
    // 2. Calculate the difference.
    //  if d = 0, set both stones to 0.
    //  if a > b, b = 0, a = a - b
    //  if a < b, a = 0, b = b - a
    // Go back to 1 until all stones have zero weight or there's
    // a single positive stones.
    // Time complexity: O(n^2)
    //
int smash_stones(vector<int>& stones)
{
    while (stones.size() > 1) {
        int first_max = remove_largest(stones);
        int second_max = remove_largest(stones);
        if (first_max - second_max != 0)
            stones.emplace_back(first_max - second_max);
    }

    return stones.size() == 0 ? 0 : stones[0];
}

int main()
{
    vector<int> tc1{2, 4, 3, 8};
    int tc1_res = 1;
    assert(smash_stones(tc1) == tc1_res);

    vector<int> tc2{1, 2, 3, 4};
    int tc2_res = 0;
    assert(smash_stones(tc2) == tc2_res);
    return 0;

}
