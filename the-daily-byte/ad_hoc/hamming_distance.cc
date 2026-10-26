/**
 * The Daily Byte
 *
 * Hamming Distance
 *
 * Given 2 integers x and y, return the hamming distance between 2 numbers.
 * Note: The hamming distance between 2 numbers is the number of bit
 * positions in which the bits differ.
 */

#include <cstdio>
#include <cassert>

/**
 * Idea: Do exclusive or to a and b to turn all the bit positions
 * that are differ to 1.
 * Extract the last bit that's 1 from the result and count up.
 *
 * Time complexity: O(s) where s are the number of
 * bit positions in which the bits differ.
 * Space complexity: O(1) since we need to allocate another
 *  32 or 64 bit field, depending on the architecture.
 */
int HammingDistance(int a, int b)
{
    int xab = a ^ b;
    int count = 0;
    while (xab) {
        count += 1;
        xab &= (xab - 1);
    }
    return count;
}

int main()
{
    assert(HammingDistance(2, 4) == 2);
    return 0;
}
