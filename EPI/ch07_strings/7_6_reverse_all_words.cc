/**
 * EPI - Chapter 07 Strings
 *
 * 06/24/2021
 *
 * Given a string containing a set of words separated by whitespace, we would
 * like to transform it to a string in which the words appear in the reverse
 * order. For example, "Alice likes Bob" transforms to "Bob likes Alice". We
 * do not need to keep the original string.
 *
 * Implement a function for reversing the words in a string s.
 *
 * Hint: It's difficult to solve this with one pass.
 */

#include <string>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <stack>
#include <algorithm>

using std::string;
using std::stringstream;
using std::stack;

/**
 * Use a stringstream to tokenize the sentence and use a stack to reverse the
 * words.
 *
 * Time complexity: O(n) with 2 passes. n is the number of characters.
 * Space complexity: O(n) with 1 stack and 1 copy of string.
 */
string reverse_all_words(string s)
{
    stack<string> stack_str;
    string res("");
    stringstream sstr(s);
    string token("");
    while (sstr >> token) {
        stack_str.emplace(token);
    }

    while (!stack_str.empty()) {
        res += stack_str.top();
        res += " ";
        stack_str.pop();
    }

    res.pop_back();
    // std::cout << res << std::endl;
    return res;
}

/**
 * EPI solution.
 * Reverse the string first. And then reverse individual words.
 *
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
string reverse_all_words_epi(string s)
{
    // Reverse the whole string.
    reverse(s.begin(), s.end());

    int start = 0, end = 0;

    // Reverse each word individually.
    while ((end = s.find(" ", start)) != string::npos) {
        reverse(s.begin() + start, s.begin() + end);
        start = end + 1;
    }
    
    // Reverse the last word.
    reverse(s.begin() + start, s.end());
    return s;
}

int main()
{
    string tc1("Alice likes Bob");
    string tc1_res("Bob likes Alice");
    assert(reverse_all_words(tc1) == tc1_res);
    assert(reverse_all_words_epi(tc1) == tc1_res);

    string tc2("This is Sparta");
    string tc2_res("Sparta is This");
    assert(reverse_all_words(tc2) == tc2_res);
    assert(reverse_all_words_epi(tc2) == tc2_res);

    return 0;
}
