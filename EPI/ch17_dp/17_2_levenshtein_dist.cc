/**
 * EPI Chapter 17 - DP
 *
 * 17.2 Compute the Levenshtein distance
 * Spell checkers make suggestions for misspelled words. Given a
 * misspelled string, a spell checker should return words in the
 * dictionary which are close to the misspelled string.
 *
 * In 1965, Vladimir Levenshtein defined the distance between 2 words as the
 * minimum number of "edits" it would take to transform the misspelled
 * word into a correct word, where a single edit is the insertion, deletion,
 * or substitution of a single character. For example, the Levenshtein
 * distance between "Saturday" and "Sundays" is 4 -- delete the first 'a'
 * and 't', substitute 'r' by 'n' and insert the trailing 's'.
 *
 * Write a program that takes 2 strings and computes the minimum number
 * of edits needed to transform the first string into the second string.
 *
 * Hint: Consider the same problem for prefixes of the 2 strings.
 */

#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <cstdio>

using std::string;
using std::vector;
using std::min;

void PrintVect(const vector<int>& v)
{
    for (const auto& e : v)
        std::cout << e << " ";
    std::cout << "\n";
}

void PrintMatrix(const vector<vector<int>>& m)
{
    for (const auto& v : m)
        PrintVect(v);
    std::cout << "\n";
}

/**
 * Idea: Identify the subproblems. Let A[0..a-1] represents the first string.
 * Let B[0..b-1] represents the second string.
 *
 * We build our solution from a top down approach:
 *
 * If A[a-1] == B[b-1] i.e. the last characters are the same in 2 strings,
 * we don't have to make any decision here. Our solution is the Levenshtein
 * distance of 2 substrings A[0..a-2] and B[0..b-2].
 *
 * If A[a-1] != B[b-1] i.e. the last characters are different in 2 strings,
 * then we will have to perform 1 action AND the smallest numbers of actions
 * from the following 3 decisions:
 *
 * 1. Transforming A[0..a-2] to B[0..b-2] and replace the last character of A
 * with the last character of B.
 * 2. Transforming A[0..a-1] to B[0..b-2] and add the last character of B to A.
 * 3. Transforming A[0..a-2] to B[0..b-1] and delete the last character of A.
 *
 * Our recurrence relation is:
 *
 * if (A[a-1] == B[b-1]) return L(A[0..a-2], B[0..b-2])
 * else return 1 + min(
 *  L(A[0..a-2], B[0..b-2]),
 *  L(A[0..a-1], B[0..b-2]),
 *  L(A[0..a-2], B[0..b-1])
 * )
 *
 * Time complexity: O(mn)
 * Space complexity: O(mn)
 */
int LevenshteinDistance(const string& str1, const string& str2)
{
    vector<vector<int>> L(str2.size() + 1, vector<int>(str1.size() + 1, 0));
    
    for (int i = 1; i <= str1.size(); i++) {
        L[0][i] = L[0][i-1] + 1;
    }

    for (int i = 1; i <= str2.size(); i++) {
        L[i][0] = L[i-1][0] + 1;
    }

    for (int i = 1; i <= str2.size(); i++) {
        for (int j = 1; j <= str1.size(); j++) {
            if (str2[i-1] == str1[j-1]) {
                L[i][j] = L[i-1][j-1];
            } else {
                int min_actions = min(L[i-1][j], L[i-1][j-1]);
                min_actions = min(min_actions, L[i][j-1]);
                L[i][j] = 1 + min_actions;
            }
        }
    }
    // printf("%d\n", L[str2.size()][str1.size()]);
    // PrintMatrix(L);
    return L[str2.size()][str1.size()];
}

int main()
{
    string tc1_a("abc");
    string tc1_b("yabd");
    int tc1_res = 2;
    assert(LevenshteinDistance(tc1_a, tc1_b) == tc1_res);

    string tc2_a("Saturday");
    string tc2_b("Sundays");
    int tc2_res = 4;
    assert(LevenshteinDistance(tc2_a, tc2_b) == tc2_res);

    string tc3_a("Carthorse");
    string tc3_b("Orchestra");
    int tc3_res = 8;
    assert(LevenshteinDistance(tc3_a, tc3_b) == tc3_res);

    return 0;
}
