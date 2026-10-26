/**
 * EPI Chapter 12 Searching
 *
 * 07/21/2021
 * 12.8 Find the Kth largest element.
 *
 * Many algorithms require as a subroutine the computation of the kth largest
 * element of an array. The first largest element is simply the largest element.
 * The nth largest element is the smallest element, where n is the legnth of
 * the array.
 *
 * For example, if the input array A = {3, 2, 1, 5, 4}, then A[3] is the first
 * largest element in A, A[0] is the third largest element in A, and A[2] is
 * the fifth largest element in A.
 *
 * Design an algorithm for computing the kth largest element in an array.
 * Assume entries are distinct.
 */

#include <vector>
#include <algorithm>
#include <cassert>
#include <queue>
#include <random>
#include <stdexcept>

using std::vector;
using std::priority_queue;

/**
 * Naive approach: Sort the array and index the kth element.
 *
 * Time complexity: O(nlogn)
 * Space complexity: O(1)
 */
int kthLargestSort(vector<int> arr, int k)
{
    std::sort(arr.rbegin(), arr.rend());
    return arr[k-1];
}

/**
 * Heap approach: Use a min heap to keep track of k largest elements.
 *
 *
 * Time complexity: O(nlogk)
 * Space complexity: O(k)
 */
int kthLargestElementHeap(const vector<int>& arr, int k)
{
    priority_queue<int, vector<int>, std::greater<>> min_heap;

    for (const auto& e : arr) {
        if (min_heap.size() == k) {
            if (min_heap.top() < e) {
                min_heap.pop();
                min_heap.emplace(e);
            }
        } else {
            min_heap.emplace(e);
        }
    }

    return min_heap.top();
}

/**
 * Partial sort and binary search approach.
 *
 * Time complexity: O(n). Worst case is O(n^2), occurs when the randomly
 *  selected pivot is the smallest or largest element in the current
 *  subarray.
 * Space complexity: O(1)
 */
template <typename Compare>
int partitionAroundPivot(vector<int>& arr, int start, int end, int pidx, Compare comp)
{
    int pval = arr[pidx];
    int new_pidx = start;
    std::swap(arr[end], arr[pidx]);
    for (int i = start; i < end; i++) {
        if (comp(arr[i], pval))
            std::swap(arr[i], arr[new_pidx++]);
    }
    std::swap(arr[new_pidx], arr[end]);
    return new_pidx;
}

template <typename Compare>
int kthLargestElemQS(vector<int>& arr, Compare comp, int k)
{
    int start = 0, end = arr.size() - 1;
    std::default_random_engine gen((std::random_device())());
    while (start <= end) {
        // Generates a random integer in [left, right]
        int pidx = std::uniform_int_distribution<int>{start, end}(gen);
        int new_pidx = partitionAroundPivot(arr, start, end, pidx, comp);
        if (new_pidx == k - 1) {
            return arr[new_pidx];
        } else if (new_pidx > k  - 1) {
            end = new_pidx - 1;
        } else {
            // new_pidx < k - 1
            start = new_pidx + 1;
        }
    }
    return -1;
}

int kthLargestElement(vector<int>& arr, int k)
{
    return kthLargestElemQS(arr, std::greater<int>(), k);
}

/**
 * Variant: Design an algorithm for finding the median of an array.
 * Let n be the size of the array.
 *
 * If n is odd, then the median is the n/2 + 1 th largest element.
 * Else if n is even, then the median is the average of the
 * n/2 th and n/2 +1 1 th largest element.
 *
 * Time complexity: O(n) on average.
 * Space complexity: O(1)
 */
float findMedian(vector<int>& arr)
{
    if (arr.size() == 0) {
        throw std::length_error("Error: array is empty.");
    } else if (arr.size() % 2 == 0) {
        // Find the n/2 th and n/2 - 1 th largest element.
        float first = kthLargestElement(arr, arr.size() / 2);
        float second = kthLargestElement(arr, arr.size() / 2 + 1);
        return (first + second) / 2.0f;
    } else {
        // arr.size() % 2 == 1
        // Find the n/2 + 1 th largest element.
        return kthLargestElement(arr, arr.size()/2 + 1);
    }
}

/**
 * Variant: Design an algorithm for finding the kth largest element in the
 * presence of duplicates. The kth largest element is defined to be A[k-1]
 * after A has been sorted in a stable manner, i.e. if A[i] = A[j] and i < j
 * then A[i] must appear before A[j] after stable sorting.
 */

/**
 * Variant: A number of apartment buildings are coming up on a new street. The
 * postal service wants to place a single mailbox on the street. Their
 * objective is to minimize the total distance that residents have to walk to
 * collect their mail each day. (Different buildings may have different numbers
 * of residents.)
 * Devise an algorithm that computes where to place the mailbox so as to
 * minimize the total distance, that residents travel to get to the mailbox.
 * Assume the input is specified as an array of building objects, where each
 * building object has a field indicating the number of residents in that
 * building, and a field indicating the building's distance from the start of
 * the street.
 */

int main()
{
    vector<int> tc1{3, 2, 1, 5, 4};

    assert(kthLargestSort(tc1, 1) == 5);
    assert(kthLargestSort(tc1, 3) == 3);
    assert(kthLargestSort(tc1, 5) == 1);
    
    assert(kthLargestElement(tc1, 1) == 5);
    assert(kthLargestElement(tc1, 3) == 3);
    assert(kthLargestElement(tc1, 5) == 1);
    
    assert(kthLargestElementHeap(tc1, 1) == 5);
    assert(kthLargestElementHeap(tc1, 3) == 3);
    assert(kthLargestElementHeap(tc1, 5) == 1);

    assert(findMedian(tc1) == 3);

    vector<int> tc2{4,3,5,6,2,1};
    assert(findMedian(tc2) == 3.5f);

    return 0;
}
