/**
 * EPI Chapter 17 DP
 *
 * The problem of finding the longest nondecreasing subsequence in a sequence
 * of integers has implications to many disciplines, including string matching
 * and analyzing card games. As a concrete instance, the length of a longest
 * nondecreasing subsequence for the array
 *
 * {0, 8, 4, 12, 2, 10, 6, 14, 1, 9}
 *
 * is 4. There are multiple longest nondecreasing subsequences, e.g.,
 * {0, 4, 10, 14} and {0, 2, 6, 9}. Note that elements of non-decreasing
 * subsequence are not required to immediately follow each other in the
 * original sequence.
 *
 * Write a program that takes as input an array of numbers and returns the
 * length of a longest nondecreasing subsequence in the array.
 *
 * Hint: Express the longest nondecreasing subsequence ending at an entry in
 * terms of the longest nondecreasing subsequence appearing in the subarray
 * consisting of preceding elements.
 */

#include <vector>
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>

using std::vector;
using std::max;

/**
 * Brute force solution: For every possible nondecreasing subsequence, keep
 * track of the maximum length. The time complexity will be O(n2^n)
 *
 * Idea for dynamic programming:
 *
 * Time complexity: O(n^2)
 * Space complexity: O(n)
 */
int LongestNondecreasingSubsequenceLength(const vector<int>& A)
{
    vector<int> max_length(A.size(), 1);
    for (size_t i = 1; i < A.size(); i++) {
        for (size_t j = 0; j < i; j++) {
            if (A[i] >= A[j])
                max_length[i] = max(max_length[i], max_length[j] + 1);
        }
    }

    return *max_element(max_length.begin(), max_length.end());
}

int main()
{
    return 0;
}
