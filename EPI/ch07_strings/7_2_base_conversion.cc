/**
 * EPI 06/23/2021 - Base Conversion
 *
 * In the decimal number system, the position of a digit is used to signify the
 * power of 10 that digit is to be multiplied with. For example, "314" denotes
 * the number 3 x 100 + 1 x 10 + 4 x 1. The base b number system generalizes
 * the decimal number system: the string "a_k-1 a_k-2 ... a_1 a_0", where
 * 0 <= a_i <= b, denotes in base-b the integer a_0 b^0 + a_1 b + ...
 * ... + a_k-1 b ^ (k - 1).
 *
 * Write a program that performs base conversion. The input is a string, an
 * integer b_1, and another integer b_2. The string represents be an integer
 * in base b_1. The output should be the string representing the integer
 * base b_2. Assume 2 <= b_1, b_2 <= 16. Use "A" to represent 10, "B" for
 * 11, ..., and "F" for 15.
 *
 * For example, if the string is "615", b1 is 7 and b2 is 13, then the result
 * should be "1A7"
 *
 * Assume 2 <= b1, b2 <= 16.
 *
 * Hint: What base can you easily convert to / from?
 */

#include <string>
#include <cassert>
#include <iostream>
#include <cstdio>
#include <algorithm>

using std::string;

string base_convert(const string& s, int b1, int b2)
{
    const char* d = "0123456789ABCDEF";

    int s_digits = static_cast<int>(s.size());

    string s_abs;
    if (s[0] == '-') {
        s_abs = s.substr(1, s.size()-1);
        s_digits -= 1;
    } else {
        s_abs = s;
    }

    string res("");

    int s_base10 = 0;
    // Convert s from base b1 back to base 10.
    for (int i = 0; i < s_digits; i++) {
        s_base10 = b1 * s_base10 + (s_abs[i] - '0');
    }
    // printf("Base 10: %d\n", s_base10);
    // Convert s_base10 to base b2.
    while (s_base10) {
        res.push_back(d[s_base10 % b2]);
        s_base10 /= b2;
    }
    
    // Flip if s is negative.
    if (s[0] == '-') res.push_back('-');

    std::reverse(res.begin(), res.end());

    return res;
}

int main()
{
    assert(base_convert("615", 7, 13) == "1A7");
    assert(base_convert("-123", 7, 13) == "-51");
    assert(base_convert("-4124", 10, 2) == "-1000000011100");
    return 0;
}
