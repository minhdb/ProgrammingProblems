/**
 * EPI Chapter 17 DP
 *
 * 17.6 The Knapsack problem
 *
 * A thief breaks into a clock store. Each clock has a weight and a value,
 * which are known to the thief. His knapsack cannot hold more than a
 * specified combined weight. His intention is to take clocks whose total value
 * is maximum subject to the knapsack's weight constraint.
 *
 * Write a program for the knapsack problem that selects a subset of items that
 * has maximum value and satisfies the weight constraint. All items have
 * integer weights and values. Return the value of the subset.
 *
 * Hint: Greedy approaches are doomed.
 */

#include <vector>
#include <algorithm>

using std::vector;
using std::sort;
using std::max;

/**
 * Idea: Consider each item at index ith, we have 2 choice: take that item or
 * don't. Thus, the solution is
 *
 * Sol(N, Items[0..i]) = Max(Sol(N - W[i]), Items[0..i-1] + V[i],
 *                          Sol(N, Items[0..i-1]))
 * If W[i] > N, then Sol(N, Items[0..i]) = Sol(N, Items[0..i-1])
 *
 * Time complexity: O(NW)
 * Space complexity: O(NW)
 */
struct Item
{
    Item(int value, int weight) : v(value), w(weight) {}; 
    int v, w;
};

int MaxValue(vector<Item>& items, int W)
{
    if (items.size() == 0) return 0;
    vector<vector<int>> dp(items.size(), vector<int>(W+1, 0));
    for (size_t w = 0; w <= W; w++) {
        if (w >= items[0].w) {
            dp[0][w] = items[0].v;
        }
    }

    for (size_t i = 1; i < items.size(); i++) {
        for (size_t w = 0; w <= W; w++) {
            if (items[i].w <= w) {
                dp[i][w] = max(dp[i-1][w-items[i].w] + items[i].v,
                                dp[i-1][w]);
            } else {
                dp[i][w] = dp[i-1][w];
            }
        }
    }

    return dp[items.size() - 1][W];
}

int main()
{
    vector<Item> tc1_items{Item(5,6), Item(11,3), Item(3,1)};
    int tc1_w = 9;
    assert(MaxValue(tc1_items, tc1_w) == 16);

    vector<Item> tc2_items{Item(10, 9)};
    int tc2_w1 = 10, tc2_w2 = 8;
    assert(MaxValue(tc2_items, tc2_w1) == 10);
    assert(MaxValue(tc2_items, tc2_w2) == 0);

    return 0;
}
