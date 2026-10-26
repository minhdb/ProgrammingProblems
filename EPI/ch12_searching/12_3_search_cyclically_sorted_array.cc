/**
 * EPI Chapter 12 Searching
 *
 * 12.3 Search a cyclically sorted array.
 *
 * An array is said to be cyclically sorted if it is possible to cyclically
 * shift its entries so that it becomes sorted. For example, the array
 *
 * < 378, 478, 550, 631, 103, 203, 220, 234, 368 >
 *
 * is cyclically sorted - a cyclic left shift by 4 leads to a sorted array.
 *
 * Design an O(logn) algorithm for finding the position of the smallest element
 * in a cylically sorted array. Assume all elements are distinct. For example,
 * for the array above, our algorithm should return 4.
 *
 * Hint: Use divide and conquer.
 */

#include <cstdio>
#include <cassert>
#include <vector>

using std::vector;

int getSmallestIdx(vector<int>& arr)
{
    int left = 0, right = arr.size() - 1;

    while ( left < right ) {
        int m = left + (right - left) / 2;
        if (arr[m] > arr[right]) {
            left = m + 1;
        } else if (arr[m] < arr[right]) {
            right = m;
        }
    }

    return left;
}

int getSmallestIdxMod(vector<int>& arr)
{
    int left = 0, right = arr.size() - 1;
    while ( left <= right ) {
        int m = left + (right - left) / 2;
        if (arr[m] > arr[right]) {
            left = m + 1;
        } else {
            if (arr[m] < arr[ ((m - 1) + arr.size()) % arr.size() ])
                return m;
            else
                right = m - 1;
        }
    }
    return -1;
}

int main()
{
    vector<int> tc1{378, 478, 550, 631, 103, 203, 220, 234, 368};
    vector<int> tc2{1,2,3,4,5,6,7,8,9};
    vector<int> tc3{2,3,4,5,6,7,1};
    vector<int> tc4{3,4,5,6,7,1,2};
    vector<int> tc5{4,5,6,7,1,2,3};
    vector<int> tc6{5,6,7,1,2,3,4};
    vector<int> tc7{6,7,1,2,3,4,5};
    vector<int> tc8{7,1,2,3,4,5,6};
    assert(getSmallestIdx(tc1) == 4);
    assert(getSmallestIdxMod(tc1) == 4);

    // assert(getSmallestIdx(tc2) == 0);
    assert(getSmallestIdxMod(tc2) == 0);

    assert(getSmallestIdx(tc3) == 6);
    assert(getSmallestIdxMod(tc3) == 6);

    assert(getSmallestIdx(tc4) == 5);
    assert(getSmallestIdxMod(tc4) == 5);

    assert(getSmallestIdx(tc5) == 4);
    assert(getSmallestIdxMod(tc5) == 4);

    assert(getSmallestIdx(tc6) == 3);
    assert(getSmallestIdxMod(tc6) == 3);

    assert(getSmallestIdx(tc7) == 2);
    assert(getSmallestIdxMod(tc7) == 2);

    assert(getSmallestIdx(tc8) == 1);
    assert(getSmallestIdxMod(tc8) == 1);

    return 0;
}
