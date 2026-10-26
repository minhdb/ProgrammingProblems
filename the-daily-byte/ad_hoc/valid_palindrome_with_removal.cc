/**
 * The Daily Byte 05/25/2021
 *
 * Give n a string and the ability to delete at most one character
 * return whether or not it can form a palindrome.
 */

#include <string>
#include <cassert>

/**
 * First approach: Let n be the length of the string and is our input.
 *
 * Then, for each character in the string, remove it and check if the current
 * string is a palindrome.
 *
 * The time complexity is O(n^3) if removal of the character takes O(n).
 * Can we do better?
 */

bool is_palindrome(const std::string &s, size_t i, size_t j)
{
    while (i < j) {
        if (s[i++] != s[j--]) return false;
    }
    return true;
}

bool is_palindrome_with_removal(const std::string s)
{
    size_t n = s.size();
    for (size_t i = 0; i < n; i++) {
        std::string s_copy(s);
        s_copy.erase(s_copy.begin()+i);
        if (is_palindrome(s_copy, 0, s_copy.size())) return true;
    }
    return false;
}

bool is_palindrome_with_removal2(const std::string &s, size_t low, size_t high, size_t count)
{
    if (count > 1) return false;

    while (low < high) {
        if (s[low] == s[high]) {
            low++; high--;
        } else {
            return is_palindrome_with_removal2(s, low+1, high, count + 1) ||
                is_palindrome_with_removal2(s, low, high-1, count + 1);
        }

    }
    return true;
}


int main()
{
    std::string tc1("abcba");
    assert(is_palindrome_with_removal(tc1));

    std::string tc2("foobof");
    assert(is_palindrome_with_removal(tc2));

    std::string tc3("abccab");
    assert(!is_palindrome_with_removal(tc3));

    return 0;
}
