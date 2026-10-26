/**
 * EPI Chapter 06 Arrays
 *
 * Write a program which takes an n x n 2D array and returns the spiral
 * ordering of the array.
 *
 * Hint: Use case analysis and divide-and-conquer.
 */

#include <cassert>
#include <vector>
#include <cstdio>

using std::vector;

void print_vect(const vector<int>& v) {
    for (const auto& e : v) {
        printf("%d ", e);
    }
    printf("\n");
}
vector<int> spiral_ordering(const vector<vector<int>>& m)
{
    int n = static_cast<int>(m.size());

    vector<int> result;

    int hinc = 0;
    int vinc = 0;
    while (result.size() != n*n) {
        // Top from left to right.
        for (int i = hinc; i < n-hinc; i++) {
            result.emplace_back(m[hinc][i]);
        }
        vinc++;
        
        // printf("top\n");
        // print_vect(result);

        // Right from top to bottom.
        for (int j = vinc; j < n-vinc; j++) {
            result.emplace_back(m[j][n-vinc]);
        }
        hinc++;

        // printf("right\n");
        // print_vect(result);

        // Bottom from right to left.
        for (int i = n - hinc; i >= hinc; i--) {
            result.emplace_back(m[n-hinc][i]);
        }

        // printf("bottom\n");
        // print_vect(result);

        // Left from down to top.
        for (int j = n - vinc; j >= vinc; j--) {
            result.emplace_back(m[j][vinc-1]);
        }

        // printf("left\n");
        // print_vect(result);
    }

    return result;
}


int main()
{
    // Test case 1
    vector<vector<int>> tc1 { {1, 2, 3}, 
                              {4, 5, 6}, 
                              {7, 8, 9}  };

    vector<int> tc1_res {1, 2, 3, 6, 9, 8, 7, 4, 5};

    assert(spiral_ordering(tc1) == tc1_res);
    
    // Test case 2
    vector<vector<int>> tc2 { {1, 2, 3, 4}, 
                              {5, 6, 7, 8}, 
                              {9, 10, 11, 12}, 
                              {13, 14, 15, 16}  };

    vector<int> tc2_res {1, 2, 3, 4, 8, 12, 16, 15, 14, 13, 9, 5, 6, 7, 11, 10 };

    assert(spiral_ordering(tc2) == tc2_res);

    // Test case 3
    vector<vector<int>> tc3 { 
        {1, 2, 3, 4, 5},
        {6, 7, 8, 9, 10},
        {11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20},
        {21, 22, 23, 24, 25}
    };

    vector<int> tc3_res{1,2,3,4,5,10,15,20,25,24,23,22,21,16,11,6,7,8,9,14,19,18,17,12,13};

    assert(spiral_ordering(tc3) == tc3_res);
    
    // Test case 4
    vector<vector<int>> tc4 {{1, 2}, {3, 4}};
    vector<int> tc4_res {1, 2, 4, 3};
    assert(spiral_ordering(tc4) == tc4_res);

    // Test case 5
    vector<vector<int>> tc5{
        {1,2,3,4,5,6},
        {7,8,9,10,11,12},
        {13,14,15,16,17,18},
        {19,20,21,22,23,24},
        {25,26,27,28,29,30},
        {31,32,33,34,35,36}
    };
    vector<int> tc5_res
    {1,2,3,4,5,6,12,18,24,30,36,35,34,33,32,31,25,19,13,7,8,9,10,11,17,23,29,28,27,26,20,14,15,16,22, 21};
    // printf("%zu\n", tc5_res.size());
    assert(spiral_ordering(tc5) == tc5_res);

    return 0;
}
