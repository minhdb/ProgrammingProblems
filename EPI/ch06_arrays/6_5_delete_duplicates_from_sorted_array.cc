/**
 * EPI Chapter 06 -- Arrays
 * 06/21/2021
 *
 * This problem is concerned with deleting repeated elements from a sorted
 * array. For example, for the array <2, 3, 5, 5, 7, 11, 11, 11, 13>,
 * then after deletion, the array is <2, 3, 5, 7, 11, 13, 0, 0, 0>. After
 * deleting repeated elements, there are 6 valid entries. There are no
 * requirements as to the values stored beyond the last valid element.
 *
 * Write a program which takes as input a sorted array and updates it so that
 * all duplicates have been removed and the remaining elements have been
 * shifted left to fill the emptied indices. Return the number of valid
 * elements. Many languages have library functions for performing this
 * operation-you cannot use these functions.
 *
 * Hint: There's an O(n) time and O(1) space solution.
 */

#include <vector>
#include <unordered_set>
#include <cassert>
#include <cstdio>
#include <algorithm>

using std::vector;
using std::unordered_set;

void print_vect(const vector<int>& v)
{
    for (const auto& e : v)
        printf("%d ", e);
    printf("\n");
}

/**
 * Brute force solution: The brute force solution iterates through the entire
 * array, check if the next element of the current array is the same as the
 * current element. If they're the same, delete it the next element and shift
 * the elements to the left. We do this until the index of the current element
 * is v.size() - 2.
 *
 * Time complexity: O(n^2) due to shifting elements for each duplicates.
 * Space complexity: O(1)
 */

void shift_left_zero_filled(vector<int> & v, size_t start_idx, int filler)
{
    if (start_idx < 1) return;

    for (size_t i = start_idx; i < v.size(); i++) {
        v[i-1] = v[i];
    }

    v[v.size() - 1] = filler;
}

void delete_dups_from_sorted_array_brute_force(vector<int>& v)
{
    if (v.size() <= 1) return;
    int filler = v[v.size()-1] + 1;
    size_t last_idx = v.size() - 1;
    for (size_t i = 0; i < v.size() - 1 && i <= last_idx; i++) {
        if (v[i] == v[i+1]) {
            shift_left_zero_filled(v, i+1, filler);
            i--;
            last_idx--;
        }
    }
}


/**
 * O(nlogn) solution: Replaces every duplicates with max_value + 1, and
 * resort the array.
 *
 * O(1) space/
 */
void delete_dups_from_sorted_array_sorted(vector<int> &v)
{
    size_t n = v.size();
    if (n <= 1) return;
    int max_value = v[n-1] + 1;
    bool dup = false;
    int cur_dup_value = 0;
    for (size_t i = 0; i < n - 1; i++) {
        if (dup) {
            if (v[i+1] == cur_dup_value)
                v[i+1] = max_value;
            else dup = false;
        } else {
            if (v[i] == v[i+1]) {
                cur_dup_value = v[i];
                v[i+1] = max_value;
                dup = true;
            }
        }
    }

    std::sort(v.begin(), v.end());
}

/**
 * O(n) solution
 * O(n) space
 *
 * Use a hash table
 */
int delete_dups_from_sorted_array_hash_set(vector<int>& arr)
{
    // Build the hash table.
    unordered_set<int> us;
    for (const auto& e : arr) {
        if (us.find(e) == us.end())
            us.emplace(e);
    }

    // Reinsert back into the array.
    size_t i = 0;
    for (const auto& e : us) {
        arr[i++] = e;
    }
    int result_idx = i;
    while (i < arr.size())
        arr[i] = 0;
    return result_idx;
}

/**
 * My personal most efficient solution. (Testing out)
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
int delete_dups_from_sorted_array_efficient(vector<int>& arr)
{
    int prev = arr[0];
    size_t valid_idx = 1;
    
    for (size_t i = 1; i < arr.size(); i++) {
        if (arr[i] != prev) {
            std::swap(arr[i], arr[valid_idx]);
            prev = arr[valid_idx++];
        }
    }

    return valid_idx;
}



/**
 * Exploit the fact that the given array is sorted.
 *
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
int delete_dups_from_sorted_array(vector<int>& v)
{
    size_t n = v.size();

    int write_idx = 1;

    for (size_t i = 1; i < n; i++) {
        // printf("write_idx: %d\t%zu\n", write_idx, i);
        if (v[write_idx - 1] != v[i]) {
            v[write_idx++] = v[i];
        }

        print_vect(v);
    }
    return write_idx;
}

int main()
{
    vector<int> tc1     {2, 3, 5, 5, 7, 11, 11, 11, 13};
    vector<int> tc1_res {2, 3, 5, 7, 11,13, 14, 14, 14};
    // delete_dups_from_sorted_array_brute_force(tc1);
    // delete_dups_from_sorted_array(tc1);
    // delete_dups_from_sorted_array_sorted(tc1);
    // assert(tc1 == tc1_res);
    // delete_dups_from_sorted_array(tc1);
    print_vect(tc1);
    printf("Unique elements: 6\n");
    int result_tc1 = delete_dups_from_sorted_array_efficient(tc1);
    print_vect(tc1);
    printf("Number of unique elements in result: %d\n", result_tc1);


    vector<int> tc2     {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    vector<int> tc2_res {1, 2, 2, 2, 2, 2, 2, 2, 2, 2};
    // delete_dups_from_sorted_array_brute_force(tc2);
    // delete_dups_from_sorted_array(tc2);
    // delete_dups_from_sorted_array_sorted(tc2);
    // assert(tc2 == tc2_res);
    // delete_dups_from_sorted_array(tc2);
    print_vect(tc2);
    printf("Unique elements: 1\n");
    int result_tc2 = delete_dups_from_sorted_array_efficient(tc2);
    print_vect(tc2);
    printf("Number of unique elements in result: %d\n", result_tc2);

    return 0;
}
