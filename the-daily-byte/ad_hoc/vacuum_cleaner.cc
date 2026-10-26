/**
 * Daily Byte 05/21/2021
 *
 * Given a string representing the sequence of moves a robot vacuum makes,
 * return whether or not it will return to its original position. The string
 * will only contain L, R, U, and D characters, representing left, right, up,
 * and down respectively.
 */

#include <string>
#include <cassert>
#include <utility>

bool will_return_to_original(const std::string& s)
{
    size_t s_len = s.size();

    std::pair<int, int> original = std::make_pair(0, 0);

    if (s_len % 2 != 0) return false;

    for (size_t i = 0; i < s_len; i++) {
        if (s[i] == 'L') {
            original.first--;
        } else if (s[i] == 'R') {
            original.first++;
        } else if (s[i] == 'U') {
            original.second++;
        } else if (s[i] == 'D') {
            original.second--;
        }
    }

    return original.first == 0 && original.second == 0;
}

int main()
{
    std::string tc1("LR");
    assert(will_return_to_original(tc1));

    std::string tc2("URURD");
    assert(!will_return_to_original(tc2));

    std::string tc3("RUULLDRD");
    assert(will_return_to_original(tc3));

    std::string tc4("RUDR");
    assert(!will_return_to_original(tc4));
}
