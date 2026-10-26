/**
 * EPI Chapter 13 Hash tables
 *
 * 13.10 Find the length of a longest contained interval.
 *
 * Write a program which takes as input a set of integers represented by an
 * array, and returns the size of a largest subset of integers in the array
 * having the property that if 2 integers are in the subset, then so are all
 * integers between them. For example, if the input is
 *
 * <3, -2, 7, 9, 8, 1, 2, 0, -1, 5, 8>
 *
 * the largest such subset is <-2, -1, 0, 1, 2, 3> so you should return 6.
 *
 * Hint: Do you really need a total ordering of the input?
 */

#include <cassert>
#include <cstdio>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using std::sort;
using std::vector;
using std::unordered_set;
using std::unordered_map;

int LongestContainedRange(const vector<int>& arr)
{
    unordered_set<int> mapper(arr.begin(), arr.end());

    int max_size = 0;
    for (const auto& e : arr) {
        int cur_size = 1;
        if (mapper.count(e) != 0) {
            int upper_bound = e + 1;
            while (mapper.count(upper_bound) != 0) {
                mapper.erase(upper_bound);
                upper_bound++;
                cur_size++;
            }

            int lower_bound = e - 1;
            while (mapper.count(lower_bound) != 0) {
                mapper.erase(lower_bound);
                lower_bound--;
                cur_size++;
            }

            mapper.erase(e);
            max_size = std::max(max_size, cur_size);
        }
        
    }
    return max_size;
}

/**
 * Sort and iterate through every subarray and check if a[i] = a[i-1] + 1.
 *
 * Time complexity: O((max - min)n^2)
 * Space complexity: O(1)
 */
int LongestContainedRangeSort(vector<int>& arr)
{
    sort(arr.begin(), arr.end());
    int max_len = 0;

    for (size_t i = 0; i < arr.size() - 1; i++) {
        for (size_t j = i+1; j < arr.size(); j++) {
            bool found = true;
            for (size_t k = i; i < j; k++) {
                if (arr[k] + 1 != arr[k+1]) {
                    found = false;
                    break;
                }
            }

            if (found) {
                max_len = std::max(max_len, static_cast<int>(j - i + 1));
            }
        }
    }
    return max_len;
}

int LongestContainedRangeEPI(const vector<int>& arr)
{
    // unprocessed_entries records the existence of each entry in A.
    unordered_set<int> unprocessed_entries(arr.begin(), arr.end());

    int max_interval_size = 0;
    while (!unprocessed_entries.empty()) {
        int a = *unprocessed_entries.begin();
        unprocessed_entries.erase(a);

        // Find the lower bound of the largest range containing a.
        int lower_bound = a - 1;

        while (unprocessed_entries.count(lower_bound)) {
            unprocessed_entries.erase(lower_bound);
            lower_bound--;
        }

        // FInd the upper bound of the largest range containing a.
        int upper_bound = a + 1;
        while (unprocessed_entries.count(upper_bound)) {
            unprocessed_entries.erase(upper_bound);
            upper_bound++;
        }

        max_interval_size = std::max(max_interval_size, upper_bound - lower_bound - 1);
    }
    return max_interval_size;
}

int main()
{
    vector<int> tc1{3, -2, 7, 9, 8, 1, 2, 0, -1, 5, 8};
    int tc1_res = 6;
    // assert(LongestContainedRangeSort(tc1) == tc1_res);
    assert(LongestContainedRange(tc1) == tc1_res);
    assert(LongestContainedRangeEPI(tc1) == tc1_res);

    vector<int> tc2{10, 5, 3, 11, 6, 100, 4};
    int tc2_res = 4;
    // assert(LongestContainedRangeSort(tc2) == tc2_res);
    assert(LongestContainedRange(tc2) == tc2_res);
    assert(LongestContainedRangeEPI(tc2) == tc2_res);

    return 0;
}
