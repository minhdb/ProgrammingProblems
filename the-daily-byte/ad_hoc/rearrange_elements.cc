/**
 * The Daily Byte
 *
 * Rearrange elements.
 *
 * Given an array of numbers, move all zeroes in the array to the end while
 * maintaining the relative order of the other numbers.
 * Note: You must modify the array you're given. (i.e. you cannot create a new
 * array)
 */

#include <vector>
#include <cassert>

using std::vector;

/**
 * Time complexity: O(n^2) due to erasing and shifting.
 * Space complexity: O(1)
 */
void RearrangeElementsBF(vector<int>& arr)
{
    int last_nonzero_idx = static_cast<int>(arr.size()-1);
    for (; last_nonzero_idx >= 0; last_nonzero_idx--) {
        if (arr[last_nonzero_idx] == 0) continue;
        else break;
    }

    for (int i = 0; i < last_nonzero_idx; i++) {
        if (arr[i] == 0) {
            arr.erase(arr.begin() + i);
            arr.emplace_back(0);
            last_nonzero_idx--;
            i--;
        }
    }
}

/**
 */
void RearrangeElements(vector<int>& arr)
{
    
}

int main()
{
    vector<int> tc1{3,7,0,5,0,2,0,0,0};
    vector<int> tc1_res{3, 7, 5, 2, 0, 0, 0, 0, 0};
    RearrangeElementsBF(tc1);
    assert(tc1 == tc1_res);

    vector<int> tc2{1,0,0,0,2,3,4,0,4,5,0,6,7,0,0,0};
    vector<int> tc2_res{1,2,3,4,4,5,6,7,0,0,0,0,0,0,0,0};
    RearrangeElementsBF(tc2);
    assert(tc2 == tc2_res);

    vector<int> tc3{1,2,3,4,5};
    vector<int> tc3_res{1,2,3,4,5};
    RearrangeElementsBF(tc3);
    assert(tc3 == tc3_res);

    vector<int> tc4{1,2,3,4,5,0,0,0,0};
    vector<int> tc4_res{1,2,3,4,5,0,0,0,0};
    RearrangeElementsBF(tc4);
    assert(tc4 == tc4_res);
    return 0;
}
