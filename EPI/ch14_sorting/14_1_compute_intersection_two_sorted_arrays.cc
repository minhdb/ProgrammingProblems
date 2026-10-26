/**
 * EPI Chapter 14 Sorting
 *
 * 07/30/2021
 *
 * A natural implementation for a search engine is to retrieve documents that
 * match the set of words in a query by maintaining an inverted index. Each
 * page is assigned an integer identifier, its document-ID. An inverted index
 * is a mapping that takes a word w and returns a sorted array of page-ids
 * which contain w - the sort order would be, for example, the page rank in
 * descending order. When a query contains multiple words, the search engine
 * finds the sorted array for each word and then computes the intersection
 * of these arrays - these are the pages containing all the words in the query.
 * The ost computationally intensive step of doing this is finding the
 * intersection of the sorted arrays.
 *
 * Write a program which takes as input 2 sorted arrays, and returns a new
 * array containing elements that are present in both of the input arrays. The
 * input arrays may have duplicate entries, but the returned array should be
 * free of duplicates.
 *
 * Hint: Solve the problem if the input array lengths differ by orders of
 * magnitude. What if they are approximately equal?
 */

#include <cstdio>
#include <vector>
#include <unordered_set>
#include <cassert>

using std::vector;
using std::unordered_set;

void PrintVect(const vector<int>& v)
{
    for (const auto e : v)
        printf("%d ", e);
    printf("\n");
}

/**
 * Idea: For each element in A, check if it's in B.
 *
 * Time complexity: O(n^2)
 * Space complexity: O(n)
 */
vector<int> IntersectTwoSortedArraysBF(const vector<int>& A, const vector<int>& B)
{
    vector<int> res;
    unordered_set<int> tracker;
    for (const auto& a : A) {
        for (const auto& b : B) {
            if (a == b && tracker.count(a) == 0) {
                res.emplace_back(a);
                tracker.emplace(a);
            }
        }
    }

    return res;
}

/**
 * Idea: Similar to merging sorted array, we maintains 2 pointers starting
 * at the beginning of 2 arrays. Increment the first / second pointer if the
 * value at that pointer is less than the value at the other pointer.
 *
 * Now we check the values at 2 pointers are the same. If they're the same,
 * add it to our list.
 *
 * Set the previous equal element.
 *
 * To handle duplicates, we keep incrementing out pointers until the values
 * at 2 pointers are not the same and not equal to prev.
 *
 * Time complexity: O(n + m)
 * Space complexity: O(1)
 */
vector<int> IntersectTwoSortedArrays(const vector<int>& A, const vector<int>& B)
{
    vector<int> res;
    int prev = 0;
    int i = 0, j = 0;
    while (i < A.size() && j < B.size()) {
        while(i < A.size() && A[i] < B[j]) {
            i++;
        }

        while (j < B.size() && B[j] < A[i]) {
            j++;
        }

        if (i < A.size() && j < B.size() && A[i] == B[j]) {
            res.emplace_back(A[i]);
            prev = A[i];
        }

        while (i < A.size() && j < B.size() && A[i] == B[j] && A[i] == prev) {
            i++;
            j++;
        }

    }
    return res;
}

int main()
{
    vector<int> tc1_A{2, 3, 3, 5, 5, 6, 7, 7, 8, 12};
    vector<int> tc1_B{5, 5, 6, 8, 8, 9, 10, 10};
    vector<int> tc1_res{5, 6, 8};
    assert(IntersectTwoSortedArraysBF(tc1_A, tc1_B) == tc1_res);
    assert(IntersectTwoSortedArrays(tc1_A, tc1_B) == tc1_res);

    vector<int> tc2_A{5, 5, 5, 5, 5, 6};
    vector<int> tc2_B{5, 6, 7, 8, 10};
    vector<int> tc2_res{5, 6};
    assert(IntersectTwoSortedArraysBF(tc2_A, tc2_B) == tc2_res);
    assert(IntersectTwoSortedArrays(tc2_A, tc2_B) == tc2_res);

    vector<int> tc3_A{1, 2, 3, 4};
    vector<int> tc3_B{5, 6, 7, 8};
    vector<int> tc3_res{};
    assert(IntersectTwoSortedArraysBF(tc3_A, tc3_B) == tc3_res);
    assert(IntersectTwoSortedArrays(tc3_A, tc3_B) == tc3_res);

    vector<int> tc4_A{1, 3, 7, 8};
    vector<int> tc4_B{0, 1, 2, 9, 10};
    vector<int> tc4_res{1};
    assert(IntersectTwoSortedArraysBF(tc4_A, tc4_B) == tc4_res);
    assert(IntersectTwoSortedArrays(tc4_A, tc4_B) == tc4_res);

    vector<int> tc5_A{2, 3, 3, 5, 7, 11};
    vector<int> tc5_B{3, 3, 7, 15, 31};
    vector<int> tc5_res{3, 7};
    assert(IntersectTwoSortedArraysBF(tc5_A, tc5_B) == tc5_res);
    assert(IntersectTwoSortedArrays(tc5_A, tc5_B) == tc5_res);

    return 0;
}
