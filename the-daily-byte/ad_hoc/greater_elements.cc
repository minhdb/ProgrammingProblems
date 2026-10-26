/**
 * The Daily Byte 06/14/2021
 *
 * Given 2 arrays of numbers, where the first array is a subset of the second
 * array, return an array containing all the next greater elemetns for each
 * element in the first array, in the second array. If there's no greater
 * element for any element, output -1 for that number.
 *
 * So the naive solution would be for each element in v1, check for the first
 * element in v2 that's greater than the current v1's element. If we can't find
 * it, add -1 to the result vector.
 * This is O(nm) time and O(n) space.
 */

#include <vector>
#include <cassert>
#include <cstdio>

using std::vector;

void print_vector(const vector<int>& v)
{
    for (const auto& e : v) {
        printf("%d ", e);
    }
    printf("\n");
}

vector<int> greater_elements(const vector<int>& v1, const vector<int>& v2)
{
    vector<int> res;
    for (const auto& e1 : v1) {
        bool found = false;
        for (const auto& e2 : v2) {
            if (e2 > e1) { 
                res.push_back(e2); 
                found = true;
                break; 
            }
        }
        
        if (!found) res.push_back(-1);
    }
    // print_vector(res);
    return res;
}


int main()
{
    vector<int> tc1_v1{4, 1, 4};
    vector<int> tc1_v2{1, 3, 4, 2};
    vector<int> tc1_res{-1, 3, -1};
    assert(greater_elements(tc1_v1, tc1_v2) == tc1_res);

    vector<int> tc2_v1{2, 4};
    vector<int> tc2_v2{1, 2, 3, 4};
    vector<int> tc2_res{3, -1};
    assert(greater_elements(tc2_v1, tc2_v2) == tc2_res);

    return 0;
}
