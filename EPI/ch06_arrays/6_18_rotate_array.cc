/**
 * EPI Chapter 06 Array.
 * Rotate 2D array.
 */

#include <vector>
#include <iostream>
#include <cstdio>
#include <cassert>

using std::vector;

void PrintMatrix(const vector<vector<int>>& m)
{
    for (const auto& v : m) {
        for (const auto& e : v) {
            printf("%d ", e);
        }
        printf("\n");
    }
    printf("\n");
}

void RotateArray(vector<vector<int>>& matrix)
{
    int n = static_cast<int>(matrix.size());
    for (int i = 0; i < n / 2; i++) {
        for (int j = i; j < n - i - 1; j++) {
            int top_tmp = matrix[i][j];
            int right_tmp = matrix[j][n - i - 1];
            int bot_tmp = matrix[n - i - 1][n - j - 1];
            int left_tmp = matrix[n -j - 1][i];

            matrix[i][j] = left_tmp;
            matrix[j][n - i - 1] = top_tmp;
            matrix[n - i - 1][n - j - 1] = right_tmp;
            matrix[n - j - 1][i] = bot_tmp;
            // PrintMatrix(matrix);
        }
    }
}

int main()
{
    vector<vector<int>> tc1{{1}};
    vector<vector<int>> tc1_result{{1}};
    RotateArray(tc1);
    assert(tc1 == tc1_result);

    vector<vector<int>> tc2{
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };  
    vector<vector<int>> tc2_result{
        {7, 4, 1},
        {8, 5, 2},
        {9, 6, 3}
    };
    RotateArray(tc2);
    assert(tc2 == tc2_result);

    vector<vector<int>> tc3{
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };
    vector<vector<int>> tc3_result{
        {13, 9, 5, 1},
        {14, 10, 6, 2},
        {15, 11, 7, 3},
        {16, 12, 8, 4}
    };
    RotateArray(tc3);
    assert(tc3 == tc3_result);

    vector<vector<int>> tc5{
        {1, 2, 3, 4, 5},
        {6, 7, 8, 9, 10},
        {11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20},
        {21, 22, 23, 24, 25}
    };
    vector<vector<int>> tc5_result{
        {21, 16, 11, 6, 1},
        {22, 17, 12, 7, 2},
        {23, 18, 13, 8, 3},
        {24, 19, 14, 9, 4},
        {25, 20, 15, 10, 5}
    };
    RotateArray(tc5);
    assert(tc5 == tc5_result);

    vector<vector<int>> tc6{
        {1, 2},
        {3, 4}
    };
    vector<vector<int>> tc6_result{
        {3, 1},
        {4, 2}
    };
    RotateArray(tc6);
    assert(tc6 == tc6_result);


    return 0;
}

