/**
 * EPI Problem 5.1
 *
 * 06/15/2021
 *
 * The parity of a binary word is 1 if the number of 1s in the word is odd;
 * otherwise, is is 0. For example, the parity of 1011 is 1, and the parity
 * of 10001000 is 0. Parity checks are used to detect single bit errors in
 * data storage and communication. It is fairly straightforward to write
 * to write code that computes the parity of a single 64-bits word.
 *
 * How would you compute the parity of a very large number of 64-bit words?
 *
 * Hint: Use a lookup table. Don't use 2^64 entries.
 */

#include <cassert>
#include <cstdio>
#include <vector>

#define P2(n) n, n ^ 1, n ^ 1, n
#define P4(n) P2(n), P2(n ^ 1), P2(n ^ 1), P2(n)
#define P6(n) P4(n), P4(n ^ 1), P4(n ^ 1), P4(n)
#define LOOK_UP P6(0), P6(1), P6(1), P6(0)


unsigned int precomputed_parity[256] = { LOOK_UP };

/**
 * Brute-force solution: Count the number of 1 and check if the number of 1s
 * is even or not.
 * Time complexity: O(n) where n is the number of bits in our input number.
 * Space complexity: O(1).
 */
short computing_parity_brute_force(long n)
{
    short count = 0;
    while (n) {
        count ^= n & 0x1;
        n >>= 1;
    }
    return count;
}

/**
 * Bit manipulation solution 1: Use y = x & ~(x - 1) to get the rightest 1
 * in x.
 *  x & (x - 1) set the lowest 1 bit to 0.
 * Time complexity: O(s) where s is the number of bits set to 1 in x.
 */
short computing_parity_clearing_set_bits(long n)
{
    short count = 0;
    while (n) {
        count ^= 0x1;
        n &= (n - 0x1);
    }
    return count;
}



/**
 * Bit manipulation solution 2: Divide 64 bits into groups of 16 bits.
 * Compute the parity of each group, and then compute the parity of
 * the parity of each group.
 * Time complexity: O(n/k) where n is the number of bits and k is the number
 * of group.
 */
short computing_parity_cache(long n)
{
    // Pre-computed parity cache
    const int k_word_size = 16;
    const int k_bit_mask = 0xFFFF;

    return precomputed_parity[ (n >> k_word_size * 3) & k_bit_mask  ] ^
            precomputed_parity[ (n >> k_word_size * 2) & k_bit_mask ] ^
            precomputed_parity[ (n >> k_word_size) & k_bit_mask ] ^
            precomputed_parity[ n & k_bit_mask ];

}

/**
 * Solution 4: The XOR of a group of bits is its parity. XOR is associative
 * and commutative.
 */
short computing_parity_xor_shift(long n)
{
    n ^= (n >> 32);
    n ^= (n >> 16);
    n ^= (n >> 8);
    n ^= (n >> 4);
    n ^= (n >> 2);
    n ^= (n >> 1);
    return n & 0x1;
}

int main()
{
    // printf("Size of integer: %zu\n", sizeof(int));
    // printf("Size of unsigned integer: %zu\n", sizeof(unsigned int));
    // printf("Size of long integer: %zu\n", sizeof(long));
    // printf("Size of unsigned long: %zu\n", sizeof(unsigned long));
    //
    assert(computing_parity_brute_force(0b1011) == 1);
    assert(computing_parity_brute_force(0b10001000) == 0);

    assert(computing_parity_brute_force(0b1011) == 1);
    assert(computing_parity_brute_force(0b10001000) == 0);

    assert(computing_parity_cache(0b1011) == 1);
    assert(computing_parity_cache(0b10001000) == 0);

    assert(computing_parity_cache(0b1011) == 1);
    assert(computing_parity_cache(0b10001000) == 0);


    assert(computing_parity_clearing_set_bits(0b1011) == 1);
    assert(computing_parity_clearing_set_bits(0b10001000) == 0);

    assert(computing_parity_clearing_set_bits(0b1011) == 1);
    assert(computing_parity_clearing_set_bits(0b10001000) == 0);


    assert(computing_parity_xor_shift(0b1011) == 1);
    assert(computing_parity_xor_shift(0b10001000) == 0);

    assert(computing_parity_xor_shift(0b1011) == 1);
    assert(computing_parity_xor_shift(0b10001000) == 0);
    return 0;
}
