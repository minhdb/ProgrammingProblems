/**
 * EPI - Chapter 07 Strings
 *
 * 06/24/2021
 *
 * Consider the following 2 rules that are to be applied to an array of
 * characters.
 *
 *  - Replace each 'a' by 2 'd's.
 *  - Delete each entry containing a 'b'.
 *
 *  For example, applying these rules to the array
 *      <a, c, d, b, b, c, a> results in the array
 *
 *      <d, d, c, d, c, d, d>
 *
 *  Write a program which takes as input an array of characters, and removes
 *  each 'b' and replaces each 'a' by 2 'd's. Specifically, along with the
 *  array, you are provided an integer-valued size. Size denotes the number
 *  of entries of the array that the operation is to be applied to. You do not
 *  have to worry preserving about subsequent entries. For example, if the
 *  array is <a, b, a, c, ...> and the size is 4, then you can return
 *  <d, d, d, d, c>. You can assume there is enough space in the array to hold
 *  the final result.
 */

#include <string>
#include <cassert>
#include <iostream>
#include <algorithm>

using std::string;

/**
 * Library solution: Use delete / insert utilities from the standard library.
 *
 * Time complexity: O(n^2) as each delete / insert takes O(n) due to shifting.
 * Space complexity: O(1)
 */
void replace_and_remove_bf(string& s)
{
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == 'b') {
            s.erase(s.begin() + i);
            i--;
        } else if (s[i] == 'a') {
            s[i] = 'd';
            s.insert(s.begin()+i+1, 'd');
        }
    }
}

/**
 * Linear solution but with auxilary array. Simulate the process and copy
 * the result to a new array.
 *
 * Time complexity: O(n)
 * Space complexity: O(n)
 */
string replace_and_remove_space(const string& s)
{
    string res("");
    for (const char& c : s) {
        if (c == 'b') {
            continue;
        } else if (c == 'a') {
            res += 'd';
            res += 'd';
        } else {
            res += c;
        }
    }
    return res;
}

/**
 * Linear solution with O(1) space.
 *
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
int replace_and_remove_opt(string& s)
{
    // std::cout << s << std::endl;
    // int old_size = static_cast<int>(s.size());

    // int write_idx = 0;

    // for (size_t i = 0; i < s.size(); i++) {
    //    if (s[i] == 'b') {
    //        write_idx = i;
    //        i++;
    //        while (s[i] == 'b') i++;
    //        while (i < s.size() && s[write_idx] == 'b') {
    //            std::swap(s[i], s[write_idx]);
    //            i++;
    //            write_idx++;
    //        }
    //    }
    // }
    //
    // std::cout << "After deleting bs: " << std::endl;
    // std::cout << s << std::endl;

    /// *
    // for (int i = 0; i < old_size; i++) {
    //    if (s[i] == 'a') s[i] = 'd';
    // }
    // */

    // Forward iteration: remove "b"s and count the number of "a"s

    int write_idx = 0, a_count = 0;
    int size = static_cast<int>(s.size());
    std::cout << s << std::endl;
    for (int i = 0; i < size; i++) {
        if (s[i] != 'b') {
            s[write_idx++] = s[i];
        }

        if (s[i] == 'a') {
            a_count++;
        }
    }

    std::cout << "After deleting bs: " << std::endl;
    std::cout << s << std::endl;

    // Backward iteration: replace "a"s with "dd"s starting from the end.
    int cur_idx = write_idx - 1;
    write_idx = write_idx + a_count - 1;
    const int final_size = write_idx + 1;
    while (cur_idx >= 0) {
        if (s[cur_idx] == 'a') {
            s[write_idx--] = 'd';
            s[write_idx--] = 'd';
        } else {
            s[write_idx--] = s[cur_idx];
        }
        cur_idx--;
    }

    std::cout << "After replacing a with dd: " << std::endl;
    std::cout << s << std::endl;
    return final_size;
}

int main()
{
    string tc1("acdbbca");
    replace_and_remove_bf(tc1);
    assert(tc1 == "ddcdcdd");

    tc1 = "acdbbca";
    assert(replace_and_remove_space(tc1) == "ddcdcdd");

    replace_and_remove_opt(tc1);

    string tc2("bbbaa");
    replace_and_remove_opt(tc2);

    string tc3("bbbbb");
    replace_and_remove_opt(tc3);

    string tc4("asdfsdfbbbsbsdafdbsba");
    replace_and_remove_opt(tc4);
    return 0;
}
