/**
 * The Daily Byte
 *
 * 07/13/2021
 *
 * Given a list of positive numbers without duplicates and a target number,
 * find all unique combinations of the numbers that sum to the target.
 * Note: You may use the same number more than once.
 */

#include <vector>
#include <string>
#include <cstdio>
#include <cassert>
#include <algorithm>

using std::vector;
using std::string;

void print_matrix(const vector<vector<int>>& m)
{
    for (const auto& v : m) {
        for (const auto& e : v) {
            printf("%d ", e);
        }
        printf("\n");
    }
}

void backtrack(vector<vector<int>>& ans, vector<int>& comb, const vector<int>& arr, int target, int start)
{
    if (target == 0 && !comb.empty()) {
        ans.emplace_back(comb);
    } else if (target < 0) {
        // Do nothing. Skip the current combination.
    } else {
        // 1. Every time we start widening our window, we create a new comb array.
        // 2. For each element, add the current element to the comb array, subtract from target.
        // 3. Backtrack.
        // 4. Remove that element from the comb array to explore other options.
        for (int i = start; i < arr.size(); i++) {
            comb.emplace_back(arr[i]);
            backtrack(ans, comb, arr, target - arr[i], i);
            comb.pop_back();
        }
    }
}

vector<vector<int>> unique_combination(const vector<int>& arr, int unique_number)
{
    vector<vector<int>> ans;
    vector<int> init_comb;
    backtrack(ans, init_comb, arr, unique_number, 0);
    return ans;
}

int main()
{
    vector<int> tc1{2, 4, 6, 3};
    int tc1_n = 6;
    vector<vector<int>> tc1_res{{2, 2, 2}, {2, 4}, {3, 3}, {6}};
    vector<vector<int>> tc1_bt = unique_combination(tc1, tc1_n);
    std::sort(tc1_bt.begin(), tc1_bt.end());
    // print_matrix(tc1_bt);
    assert(tc1_bt == tc1_res);
    return 0;
}
