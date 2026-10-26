/**
 * The Daily Byte
 *
 * 07/14/2021
 * Given a string s, return all possible partitions of s such that each
 * substring is a palindrome.
 */

#include <vector>
#include <string>
#include <cassert>

using std::vector;
using std::string;

void printMatrix(const vector<vector<string>>& m)
{
    for (const auto& v : m) {
        for (const auto& e : v) {
            printf("%s ", e.c_str());
        }
        printf("\n");
    }
}

bool isPalindrome(const string& s, int i, int j)
{
    while (i < j) if (s[i++] != s[j--]) return false;
    return true;
}

void backtrack(vector<vector<string>>& res, vector<string>& cur, const string& s, int start)
{
    if (start >= static_cast<int>(s.size())) res.emplace_back(cur);
    for (int end = start; end < static_cast<int>(s.size()); end++) {
        if (isPalindrome(s, start, end)) {
            cur.emplace_back(s.substr(start, end - start + 1));
            backtrack(res, cur, s, end + 1);
            cur.pop_back();
        }
    }
}

vector<vector<string>> palindrome_splitting(const string& s)
{
    vector<vector<string>> res;
    vector<string> cur;
    backtrack(res, cur, s, 0);
    return res;
}

int main()
{
    string tc1("abcba");
    vector<vector<string>> tc1_res{
        {"a", "b", "c", "b", "a"},
        {"a", "bcb", "a"},
        {"abcba"}
    };
    // printMatrix(palindrome_splitting(tc1));
    assert(palindrome_splitting(tc1) == tc1_res);
    return 0;
}
