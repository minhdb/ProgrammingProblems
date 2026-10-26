/**
 * EPI - Chapter 5 Primitive types
 *
 * 5.2 Swap bits
 * There are number of ways in which bit manipulations can be accelerated. For
 * example, as described, the expression x & (x-1) clears the lowest set bit in
 * x, and x & ~(x-1) extracts the lowest set bit of x.
 *
 * A 64-bit integer can be viewed as an array of 64 bits, with the bit at index
 * 0 correspnding to the LSB and the bit at index 63 corresponding to the MSB.
 * Implement code that takes as input a 64-bit integer and swaps the bits at
 * indices i and j.
 *
 * Hint: When's the swap necessary?
 */

#include <cassert>
#include <cstdio>
#include <algorithm>

/**
 * BF solution: Perform a check of i and j and ensure that
 *
 * i < j.
 *
 * Extract the ith bit and jth bits using 2 masks.
 *
 * (x >> i) & 0x1;
 * (x >> j) & 0x1;
 *
 * And apply the bits to the correct positions. The operation to use depends on
 * if that bit is set or not.
 *
 * if (bit_j == 0)
 *  res &= ~(0x1 << i);
 * else
 *  res |= bit_j;
 *
 * if (bit_i == 0)
 *  res &= ~(0x1 << j);
 * else
 *  res |= bit_i;
 *
 * Example;
 * 1100 0100 where i = 1 and j = 6
 *
 * 1000 0110
 *
 * bit_j = 0000 0001
 * bit_i = 0000 0000
 *
 * bit_j <<= i; 0000 0010
 * bit_i <<= j; 0000 0000
 */
long SwapBits(long x, int i, int j)
{
    if (i > j)
        std::swap(i, j);

    // Always: i < j.
    long bit_i = ((x >> i) & 0x1) << j;
    long bit_j = ((x >> j) & 0x1) << i;

    if (bit_i)
        x |= bit_i;
    else
        x &= ~(0x1 << j);

    if (bit_j)
        x |= bit_j;
    else
        x &= ~(0x1 << i);
    
    return x;
}

// There is better approach. Here's a solution in EPI.
// First, check if the 2 bits are the same, if not, don't swap.
// Otherwise, swapping them is the same as flipping their individual values.
//
long SwapBitsEPI(long x, int i, int j)
{
    // Extract the i-th and j-th bits, and see if they differ.
    if (((x >> i) & 0x1) != ((x >> j) & 0x1)) {
        // i-th and j-th bits differ. We'll swap them by flipping their values.
        // Select the bits to flip with bit_mask. Since x^1 = 0 when x = 1 and
        // x^1 = 1 when x = 0, we can perform the flip XOR.
        unsigned long bit_mask = (1L << i) | (1L << j);
        x ^= bit_mask;
    }
    return x;
}

int main()
{
    assert(SwapBits(73, 1, 6) == 11);
    assert(SwapBitsEPI(73, 1, 6) == 11);
    return 0;
}
