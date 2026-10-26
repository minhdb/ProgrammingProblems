/**
 * EPI Chatper 12 Searching
 *
 * 12.1 Search a sorted array for first occurence of k.
 *
 * Binary search commonly asks for the index of any element
 * of a sorted array that is equal to a specified element. The following
 * problem has a slight twist on this.
 *
 * Write a method that takes a sorted array and a key and returns the index
 * of the first occurence of that key in the array. For example, when applied
 * to the array, your algorithm should return 3 if the given key is 108;
 * if it is 285, your algorithm should return 6.
 */

#include <vector>
#include <cassert>

using std::vector;

/**
 * Binary search does not guarantee to get the first occurence.
 * Since the array's sorted, once we have found an existing element k,
 * we keep moving left until wee don't see k anymore.
 *
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
int FirstOccurence(const vector<int>& arr, int k)
{
    size_t i = 0, j = arr.size() - 1;
    int first_occurence = -1;
    while (i <= j) {
        size_t m = i + (j - i) / 2;
        if (arr[m] == k) {
            first_occurence = static_cast<int>(m);
            break;
        } else if (arr[m] < k) {
            i = m + 1;
        } else {
            j = m - 1;
        }
    }

    // printf("Found %d at %d\n", k, first_occurence);
    if (first_occurence > 0) {
        while (first_occurence >= 0 && arr[first_occurence] == k)
            first_occurence--;
        first_occurence++;
    }
    // printf("%d\n", first_occurence);
    return first_occurence;
}

/**
 * The idea of binary search is that we keep the set of possible candidates in
 * a range [lower, upper]. Once we have found a candidate, we elminiate all
 * subsequent elements.
 *
 * So our range now is updated to [lower, mid - 1].
 *
 * Time complexity: O(logN)
 * Space complexity: O(1)
 */
int FirstOccurenceLogN(const vector<int>& arr, int k)
{
    int i = 0, j = arr.size() - 1;
    int first_occurence = -1;
    while (i <= j) {
        int m = i + (j - i) / 2;
        if (arr[m] == k) {
            first_occurence = m;
            j = m - 1;
        } else if (arr[m] < k) {
            i = m + 1;
        } else {
            j = m - 1;
        }
    }
    return first_occurence;
}

int main()
{
    vector<int> tc1{-14, -10, 2, 108, 108, 243, 285, 285, 285, 401};
    assert(FirstOccurence(tc1, 108) == 3);
    assert(FirstOccurence(tc1, 285) == 6);
    assert(FirstOccurenceLogN(tc1, 108) == 3);
    assert(FirstOccurenceLogN(tc1, 285) == 6);

    vector<int> tc2{4,4,4,4,4,4,4,4};
    assert(FirstOccurence(tc2, 4) == 0);
    assert(FirstOccurenceLogN(tc2, 4) == 0);

    vector<int> tc3{1,2,5,6,7,8,9,10,13,14};
    assert(FirstOccurence(tc3, 1) == 0);
    assert(FirstOccurenceLogN(tc3, 1) == 0);

    vector<int> tc4{1,1,1,2,3,4,5,6,7,8,10,12};
    assert(FirstOccurence(tc4, 1) == 0);
    assert(FirstOccurenceLogN(tc4, 1) == 0);

    vector<int> tc5{0,1,1,2,3,4,5,6,7,8,10,12};
    assert(FirstOccurence(tc5, 1) == 1);
    assert(FirstOccurenceLogN(tc5, 1) == 1);

    return 0;
}
