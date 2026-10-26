/**
 * EPI Chapter 16 Recursion
 *
 * An n-bit Gray code is a permutation of {0, 1, 2, ..., 2^n - 1} such that
 * the binary representations of successive integers in the sequence differ in
 * only one place. (This is with wraparound, i.e., the last and first elements
 * must also differ in only one place.) For example, both
 *
 * {000, 100, 101, 111, 110, 010, 011, 001} = {0, 4, 5, 7, 6, 2, 3, 1}
 * and {0, 1, 3, 2, 6, 7, 5, 4} are Gray codes for n = 3.
 *
 * Write a program which takes n as input and returns an n-bit Gray code.
 */

#include <vector>
#include <unordered_set>

using std::vector;
using std::unordered_set;

void PrintVector(const vector<int>& v)
{
    for (const auto& e : v) {
        printf("%d ", e);
    }
    printf("\n");
}

bool differOnlyOneBit(int a, int b)
{
    int diff_xor = a ^ b;
    return (diff_xor & (diff_xor - 1)) == 0; 
}

/**
 * 1. Choice: Modifying any bit in a n-bit number.
 * 2. Goal: Generated a sequence of 2^n numbers that is a permutation of
 * {0, 1, 2, ..., 2^n - 1}
 * 3. Constraints:
 *  +) First number starts with 0.
 *  +) Adjacent numbers differ in only 1 bit.
 *  +) First and last number should also differ in 1 bit.
 */
bool DirectedGrayCode(vector<int>& res, unordered_set<int>& history, int n)
{
    if ((0x1 << n) == static_cast<int>(res.size())) {
        return (differOnlyOneBit(res.front(), res.back()));
    } else {
        int prev_code = res.back();
        for (int i = 0; i < n; i++) {
            int candidate_code = prev_code ^ (0x1 << i);
            if (history.count(candidate_code) == 0) {
                history.emplace(candidate_code);
                res.emplace_back(candidate_code);
                if (DirectedGrayCode(res, history, n)) {
                    return true;
                }
                history.erase(candidate_code);
                res.pop_back();
            }
        } 
        return false;
    }
}

vector<int> GrayCode(int n)
{
    vector<int> res{0};
    unordered_set<int> history{0};
    DirectedGrayCode(res, history, n);
    return res;
}

int main()
{
    vector<int> tcs{2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (const auto& tc : tcs) {
        PrintVector(GrayCode(tc));
    }
    return 0;
}
