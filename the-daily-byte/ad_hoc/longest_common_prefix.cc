/**
 * The Daily Byte 05/24/2021
 *
 * Given an array of strings, return the longest common prefix that is shared
 * amongst all strings. You may assume all strings only contain lowercase
 * alphabetical characters.
 */

#include <string>
#include <cassert>
#include <vector>
#include <iostream>
#include <cstdio>
#include <limits>

std::string longest_common_prefix(const std::vector<std::string> &arr)
{
    std::string result("");

    size_t n = arr.size();
    if (n == 0) return result;

    size_t min_len = std::numeric_limits<unsigned int>::max();
    for (auto s : arr) {
        if (s.size() < min_len) min_len = s.size();
    }

    size_t index = 0;
    char prev = arr[0][index];
    do {
        prev = arr[0][index];
        for (size_t i = 1; i < n; i++)
            if (prev != arr[i][index])
                return result;

        result += prev;
        index++;

    } while (index < min_len);

    return result;
}

int main()
{
    std::vector<std::string> tc1 {"colorado", "color", "cold"};
    assert(longest_common_prefix(tc1) == "col");

    std::vector<std::string> tc2 {"a", "b", "c"};
    assert(longest_common_prefix(tc2) == "");

    std::vector<std::string> tc3 {"spot", "spotty", "spotted"};
    assert(longest_common_prefix(tc3) == "spot");
    return 0;
}

