/**
 * EPI Chapter 16 Recursion
 *
 * 16.4 Generate the power set
 *
 * The power set of a set S is the set of all subsets of S, including both the
 * empty set and S itself.
 *
 * Write a function that takes as input a set and returns its power set.
 *
 * Hint: There are 2^n subsets for a given set of S of size n. There are
 * 2^k k-bit words.
 */

#include <vector>
#include <cmath>
#include <string>
#include <unordered_set>
#include <algorithm>

using std::string;
using std::unordered_set;
using std::vector;
using std::sort;

void PrintMatrix(const vector<vector<int>>& m)
{
    for (const auto& v : m) {
        for (const auto& e : v) {
            printf("%d ", e);
        }
        printf("\n");
    }
    printf("\n");
}

/**
 * Idea: We compute all subset U and V such that U contains a particular
 * element and V does not contain that same element. Our result is
 *
 * Res = U union V.
 *
 * Time complexity: O(n2^n) because C(n) = 2C(n - 1).
 * Space complexity: On(n2^n) since there are 2^n subsets.
 */
void DirectedPowerSet(const vector<int>& input_set, vector<vector<int>>&
        res, vector<int>& cur, int selecting_idx)
{
    if (selecting_idx == input_set.size()) {
        res.emplace_back(cur);
    } else {
        // Generate subsets that contain nums[selecting_idx].
        cur.emplace_back(input_set[selecting_idx]);
        DirectedPowerSet(input_set, res, cur, selecting_idx + 1);

        // Generate subsets that don't contain nums[selecting_idx].
        cur.pop_back();
        DirectedPowerSet(input_set, res, cur, selecting_idx + 1);
    }
}

vector<vector<int>> GeneratePowerSet(const vector<int>& input_set) {
    vector<vector<int>> power_set;
    vector<int> cur;
    DirectedPowerSet(input_set, power_set, cur, 0);
    return power_set;
}

/**
 * Idea: There are 2^n subsets for a set of n elements.
 * Just like there are 2^k k-bit words.
 *
 * Time complexity: O(n2^n)
 * Space complexity: O(2^n) but can be reduced to just O(n) if we want to
 * enumerate just subset i.e. printing out.
 */
vector<vector<int>> GeneratePowerSetBitwise(const vector<int>& input_set)
{
    vector<vector<int>> power_set;
    for (int int_for_subset = 0; int_for_subset < (1 << input_set.size());
            int_for_subset++) {
        int bit_array = int_for_subset;
        vector<int> subset;

        while (bit_array) {
            subset.emplace_back(input_set[log2(bit_array & ~(bit_array - 1))]);
            bit_array &= bit_array - 1;
        }
        power_set.emplace_back(subset);
    }
    return power_set;
}

/**
 * Variant: Solve this problem when the input array may have duplicates, i.e.
 * denotes a multiset. You should not repeat any multiset.
 *
 * Idea: sorting helps us identify duplicate subsets.
 *
 * Time complexity: O(n^2 2^n) since we need to compare 2 arrays.
 * Space complexity: O(2^n) at worst.
 */
void DirectedGeneratePowerSetWithDup(vector<vector<int>>& res,
        vector<int>& cur, vector<int>& nums, int selecting_idx)
{
    if (selecting_idx == nums.size()) {
        res.emplace_back(cur);
    } else {
        cur.emplace_back(nums[selecting_idx]);
        if (res.empty() || res.back() != cur) {
            DirectedGeneratePowerSetWithDup(res,
                    cur, nums, selecting_idx+1);
        }
        cur.pop_back();
        DirectedGeneratePowerSetWithDup(res,
                cur, nums, selecting_idx+1);
    }
}

vector<vector<int>> GeneratePowerSetWithDup(vector<int>& nums)
{
    vector<vector<int>> res;
    vector<int> cur;
    sort(nums.begin(), nums.end());
    DirectedGeneratePowerSetWithDup(res, cur, nums, 0);
    return res;
}

/**
 * Bitwise version for duplicates
 */
vector<vector<int>> GeneratePowerSetWithDupBitwise(vector<int>& nums)
{
    sort(nums.begin(), nums.end());
    unordered_set<string> seen;
    vector<vector<int>> res;
    for (size_t int_as_subset = 0; int_as_subset < (1 << nums.size());
            int_as_subset++) {
        vector<int> cur;
        string cur_str("");
        int bit_array = int_as_subset;
        while (bit_array) {
            cur.emplace_back(nums[log2(bit_array & ~(bit_array - 1))]);
            cur_str += (nums[log2(bit_array & ~(bit_array - 1))]);
            bit_array &= (bit_array - 1);
        }

        if (seen.count(cur_str) == 0) {
            seen.emplace(cur_str);
            res.emplace_back(cur);
        }
    }
    return res;
}

int main()
{
    vector<int> tc1{1, 2, 3, 4};
    printf("Unique bitwise ver:\n");
    PrintMatrix(GeneratePowerSetBitwise(tc1));
    printf("Unique backtracking ver:\n");
    PrintMatrix(GeneratePowerSet(tc1));

    vector<int> tc2_dup{1, 2, 2, 3};
    printf("Dups backtracking ver:\n");
    PrintMatrix(GeneratePowerSetWithDup(tc2_dup));
    printf("Dups bitwise ver:\n");
    PrintMatrix(GeneratePowerSetWithDupBitwise(tc2_dup));
    return 0;
}   
