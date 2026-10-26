/**
 * EPI Chapter 14 Sorting
 *
 * 07/30/2021
 * 14.2 Merge two sorted arrays
 *
 * Supposed you are given two sorted arrays of integers. If one array has
 * enough empty entries at its end, it can be used to store the combined
 * entries of the 2 arrays in sorted order. For example, consider
 *
 * <5, 13, 17, ., ., ., ., .>
 *
 * and
 *
 * <3, 7, 11, 19> where . denotes an empty entry.
 *
 * Then the combined sorted entries can be stored in the first array as
 *
 * <3, 5, 7, 11, 13, 17, 19, .>
 *
 * Write a program which takes as input 2 sorted arrays of integers, and
 * updates the first to be combined entries of the 2 arrays in sorted order.
 * Assume the first array has enough empty entries at its end to hold the
 * result.
 */

#include <vector>
#include <cassert>
#include <cstdio>

using std::vector;

void PrintVect(const vector<int>& arr)
{
    for (const auto& e : arr)
        printf("%d ", e);
    printf("\n");
}

/**
 * Idea: Start filling the first array from the end of it. The first element to
 * fill is n + m - 1
 *
 * Time complexity: O(m + n)
 * Space complexity: O(1)
 */
void MergeTwoSortedArraysMyEPI(vector<int>& nums1, int m, 
        const vector<int>& nums2, int n)
{
   if ( n == 0 ) return;

   int i = m - 1;
   int j = n - 1;
   int b = n + m - 1;

   while (i >= 0 && j >= 0 && b >= 0) {
       if (nums1[i] > nums2[j]) {
           nums1[b--] = nums1[i--];
       } else {
           nums1[b--] = nums2[j--];
       }
   }
    
   while (i >= 0 && b >= 0)
       nums1[b--] = nums1[i--];

   while (j >= 0 && b >= 0) {
       nums1[b--] = nums2[j--];
   }
}

void MergeToSortedArraysEPI(vector<int>& A, int m,
        const vector<int>& B, int n)
{
    int a = m - 1, b = n - 1, write_idx = m + n - 1;
    while (a >= 0 && b >= 0)
        A[write_idx--] = A[a] > B[b] ? A[a--] : B[b--];

    while (b >= 0)
        A[write_idx--] = B[b--];
}

/**
 * My idea: move all elements from the first array to the end of the array
 * and perform merge sort.
 *
 * Time complexity: O(n + m)
 * Space complexity: O(1)
 */
void MergeTwoSortedArraysLC(vector<int>& nums1, int m
        , const vector<int>& nums2, int n)
{
    if (n == 0) return;

    int i = 0, j = 0, blank = 0;

    int nums1_len = static_cast<int>(nums1.size());

    j = nums1_len - 1;

    for (i = m - 1; i >= 0; i--) {
        nums1[j--] = nums1[i];
    }

    i = j + 1; j = 0;
    while (j < n && i < nums1_len && m > 0) {
        if (nums2[j] < nums1[i]) {
            nums1[blank++] = nums2[j++];
        } else {
            nums1[blank++] = nums1[i++];
            m--;
        }
    }

    while (blank < nums1_len && j < n)
        nums1[blank++] = nums2[j++];

    while (blank < nums1_len && i < nums1_len)
        nums1[blank++] = nums1[i++];
}

bool MyEqual(const vector<int>& A, const vector<int>& B)
{
    size_t min_len = A.size() < B.size() ? A.size() : B.size();
    for (size_t i = 0; i < min_len; i++)
        if (A[i] != B[i]) return false;
    return true;
}


int main()
{
    vector<int> tc1_A{5, 13, 17, 0, 0, 0, 0, 0};
    int tc1_m = 3;
    vector<int> tc1_B{3, 7, 11, 19};
    int tc1_n = 4;
    vector<int> tc1_res{3, 5, 7, 11, 13, 17, 19, 0};
    MergeTwoSortedArraysLC(tc1_A, tc1_m, tc1_B, tc1_n);
    MyEqual(tc1_A, tc1_res);
    return 0;
}

