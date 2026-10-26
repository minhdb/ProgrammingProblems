/**
 * HRT Task 2
 *
 * A string S consisting of the letters A, B, C, and D is given. The string can
 * be transformed either by removing a letter A together with an adjacent
 * letter B, or by removing a letter C together with an adjacent letter D.
 *
 * Write a function that given a string S of N characters, returns any string that:
 *
 * Can be obtained from S by repeatedly applying the described transformation, and
 * cannot be further transformed.
 *
 * If at some point there is more than one possible way to transform the string, any
 * of the valid transformations may be chosen.
 *
 * Examples:
 * 1. Given S = "CBACD", the function may return "C", because one of the
 * possible sequences of operation is as follows:
 *
 * CBACD -> CBA -> C
 *
 * 2. Given S = "CABABD" the function may return an empty string, because one
 * possible sequence of operations is:
 *
 * CABABD -> CABD -> CD -> """
 *
 * 3. Given string S = "ACBDACBD" the function should return "ACBDACBD",
 * because no operation can be applied to string S.
 *
 * Write an efficient algorithm for the following assumptions:
 * The length of S is within the range [0..250,000];
 * String S consists only of the following characters: "A", "B", "C", and/or "D".
 */

#define MAX_SIZE 250001

#include <string>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cassert>

using std::string;

/**
 * Brute force solution: Use recursion and reduce the string.
 *
 * Time complexity: O(N^2)
 * Space complexity: O(1)
 */
string Transform(string& S)
{
    size_t idx = 0;
    if ((idx = S.find("AB")) != string::npos ||
        (idx = S.find("BA")) != string::npos ||
        (idx = S.find("CD")) != string::npos ||
        (idx = S.find("DC")) != string::npos) {
        S.erase(idx, 2);
        return Transform(S);
    }
    return S;
}

int main()
{
    std::string test_case;
    std::string solution;
    std::ifstream test_cases_file("HRT_Task2_In");
    std::ifstream solutions_file ("HRT_Task2_Out");
    size_t test_count = 0;

    while (std::getline(test_cases_file, test_case) &&
           std::getline(solutions_file, solution)) {
        assert(Transform(test_case) == solution);
        test_count++;
        printf("Passed %zu tests.\n", test_count);
    }
    
    return 0;
}
