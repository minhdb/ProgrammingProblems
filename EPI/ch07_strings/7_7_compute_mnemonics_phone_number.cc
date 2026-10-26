/**
 * EPI - Chapter 07 Strings
 *
 * Each digit, apart from 0 and 1, in a phone key pad, corresponds to one of 3
 * or 4 letters of the alphabet, as shown. Since words are easier to remember
 * than numbers, it is natural to ask if a 7 or 10-digit phone number can be
 * represented by a word. For example, "2276696" corresponds to "ACRONYM" as
 * well as "ABPOMZN".
 *
 *
 *  ------------------
 *  |    | ABC | DEF |
 *  | 1  |  2  |  3  |
 *  ------------------
 *  | GHI| JKL | MNO |
 *  |  4 |  5  |  6  |
 *  ------------------
 *  |PQRS| TUV | WXYZ|
 *  | 7  |  8  |  9  |
 *  ------------------
 *  | *  |  0  |  #  |
 *  ------------------
 *
 *  Write a program which takes as input a phone number, specified as a string
 *  of digits, and returns all possible character sequences that correspond to
 *  the phone number. The cell phone keypad is specified by a mapping that
 *  takes a digit and returns the corresponding set of characters. The
 *  character sequences do not have to be legal words or phrases.
 */

#include <vector>
#include <cassert>
#include <string>
#include <iostream>
#include <algorithm>

using std::string;
using std::vector;


static const string KeyPad[10] = 
    {"", "", "ABC", "DEF", "GHI", "JKL", "MNO", "PQRS", "TUV", "WXYZ"};

void print_vect(const vector<string>& v)
{
    for (const auto& s : v) {
        std::cout << s << std::endl;
    }
}

/**
 * Using recursion to list out all possible representations of a phone number.
 * Base case: when s has 1 digit.
 * Inductive case: when s has n digit. For each possible value of s[0], append
 * the results gotten from calling phone_mnemonic_aux(s.substr(1, s.size() - 1)).
 *
 * Let n be the length of the string s.
 *
 * Time complexity: O(n4^n)
 * Space complexity: O(4^n) since each digit has either 0, 3, or 4 choices.
 */
vector<string> phone_mnemonic_aux(string s)
{
    vector<string> res;
    if (s.size() == 1) {
        for (auto c : KeyPad[s[0] - '0']) {
            string c_s(1, c);
            res.emplace_back(c_s);
        }
    } else if (s.size() > 1) {
        vector<string> smaller_str = phone_mnemonic_aux(s.substr(1, s.size() - 1));
        for (auto c : KeyPad[s[0] - '0']) {
            for (auto& smaller_s : smaller_str) {
                res.emplace_back(c + smaller_s);
            }
        }
    }
    return res;
}

vector<string> PhoneMnemonic(const string& phone_number)
{
    vector<string> result;
    result = phone_mnemonic_aux(phone_number);
    return result;
}

int main()
{
    vector<string> tc1 = PhoneMnemonic("2276696");
    assert(find(tc1.begin(), tc1.end(), "ACRONYM") != tc1.end());
    assert(find(tc1.begin(), tc1.end(), "ABPOMZN") != tc1.end());
    print_vect(tc1);
    return 0;
}

