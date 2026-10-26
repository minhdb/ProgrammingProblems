/**
 * The Daily Byte 05/27/2021
 *
 * Given a string representing your stones and another string representing
 * a list of jewels, return the number of stones that you have that are also
 * jewels.
 *
 * Given that the length of the jewels string is n
 * Given that the length of the stones string is m
 *
 *
 * There are 2 solutions:
 * O(nm) / O(1) - We traverse the stones string character by character and
 *  check if such character is found in the jewels string.
 *
 * O(m) / O(n) - Use a hash table to store each unique character in jewels.
 *  Traverse the stones string and check if it's in the hash table.
 */

#include <string>
#include <unordered_set>
#include <cassert>

using std::string;
using std::unordered_set;

size_t stones_that_are_jewels(const string& jewels, const string& stones)
{
    size_t stones_are_jewels = 0;
    unordered_set<char> s;
    for (auto c : jewels) s.insert(c);

    for (auto c : stones) {
        if (s.find(c) != s.end())
            stones_are_jewels++;
    }
    return stones_are_jewels;
}

int main()
{
    string tc1_j("abc");
    string tc1_s("ac");
    assert(stones_that_are_jewels(tc1_j, tc1_s) == 2);

    string tc2_j("Af");
    string tc2_s("AaaddfFf");
    assert(stones_that_are_jewels(tc2_j, tc2_s) == 3);

    string tc3_j("AYOPD");
    string tc3_s("ayopd");
    assert(stones_that_are_jewels(tc3_j, tc3_s) == 0);
    return 0;
}
