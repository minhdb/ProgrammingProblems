/**
 * LC162 Find Peak Element
 * A peak element is an element that is strictly greater than its
 * neighbors.
 *
 * Given a integer array nums, find a peak element, and return its index.
 * If the array contains multiple peaks, return the index to any of the peaks.
 *
 * You may imagine that nums[-1] = nums[n] = -inf
 */

#include <vector>
#include <cassert>

using std::vector;

size_t findPeak(const vector<int>& arr)
{
    size_t left = 0, right = arr.size() - 1;
    while (left <= right) {
        size_t mid = left + ((right - left) >> 1);

    }
    return left;
}

int main()
{
    vector<int> tc1{1,2,3,1};
    vector<int> tc2{1,2,1,3,5,6,4};
    assert(findPeak(tc1) == 2);
    assert(findPeak(tc2) == 6 || findPeak(tc2) == 1 || findPeak(tc2));
    return 0;
}
