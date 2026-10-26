/**
 * EPI Chapter 5 - Primitive types
 *
 * 5.4 Find a closest integer with the same weight.
 *
 * Define the weight of a nonnegative integer x to be the number of bits that
 * are set to 1 in its binary representation. For example, since 92 in base 2
 * is 1011100, the weight of 92 is 4.
 *
 * Write a program which takes as input a nonnegative integer x and returns a
 * number y which is not equal to x, but has the same weight as x and their
 * difference, |y - x| is as small as possible. You can assume x is not 0, or
 * all 1s. For example, if x = 6, return 5.
 *
 * Hint: Start with the least significant bit.
 */

#include <cassert>
#include <stdexcept>
/**
 * BF solution: Find out the weight of the number x. We can do so by repeatedly
 * extract the last 1s and simply count. Let that weight be w.
 *
 * After that, we try to generate all number such that it has weight w and find
 * the number y such that |y - x| is smallest.
 *
 * This will take O( C(w, n) ).
 *
 * Complicated to code the complete solution. We need a different approach.
 */

/**
 * It's safe to assume that our input's not going to be all 0s or all 1s.
 *
 * Conjecture: If the LSB is 1, move it to the nearest 0.
 * Otherwise, turn off the last 1 digit to 0 and turn on the LSB to 1.
 *
 * Time complexity: O(n) where n is the number of bits.
 *
 * NOT CORRECT.
 */
int ClosestIntSameWeight(int x)
{
    int res = x;
    unsigned int mask = 0x1;
    if ((x & 0x1) == 1) {
        mask <<= 0x1;
        while ( (x & mask) != 0)
            mask <<= 0x1;
        res |= mask;
        res &= 0x1;
    } else {
        int last_one = x & ~(x - 1);
        res ^= last_one;
        res |= 0x1;
    }
    return res;
}

/**
 * Idea: Swap the 2 rightmost consecutive bits that differ.
 *
 * Time complexity: O(n). This problem can further be solved using only O(1).
 */
const int kNumUnsignBits = 64;
unsigned long ClosestIntSameWeightEPI(unsigned long x)
{
    for (int i = 0; i < kNumUnsignBits - 1; i++) {
        if (((x >> i) & 0x1) != (( x >> (i + 1) & 0x1))) {
            // Swap bit-i and bit-(i+1)
            x ^= (1UL << i) | (1UL << (i + 1));
            return x;
        }
    }
    // Throw error if all bits of x are 0 or 1.
    throw std::invalid_argument("All bits are 0 or 1");
}

int main()
{
    assert(ClosestIntSameWeight(6) == 5);
    assert(ClosestIntSameWeight(92) == 89);
    return 0;
}
