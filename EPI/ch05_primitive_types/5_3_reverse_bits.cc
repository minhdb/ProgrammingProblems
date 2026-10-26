/**
 * EPI Chapter 05 Primitive Types
 *
 * Write a program that takes a 64-bit word and returns the 64-bit word
 * consiting of the bits of the input word in reverse order.
 *
 * Hint: Use a look up table.
 *
 * Brute force solution would be: convert the number to a string of its
 *  binary reprentation, reverse it, and convert it back to a 64-bit number.
 *  Time complexity would be O(n) where n is the number of bits.
 *
 * Solution using a look up table:
 */

#include <cstdio>
#include <cassert>
#include <vector>

using std::vector;

vector<unsigned long> generate_reverse_table()
{
    // long reverse_table_16_bits[2 >> 16];

    // long* reverse_table_16_bits = new long[2 >> 16];

    vector<unsigned long> reverse_table_16_bits(1 << 16, 0);

    unsigned long reverse_table_4_bits[16] = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};


    const int mask = 0xF;
    const int group = 0x4;
    
    for (size_t i = 0; i < (1 << 16); i++) {
        reverse_table_16_bits[i] = (reverse_table_4_bits[i & mask] << group * 3) |
                            (reverse_table_4_bits[(i >> group) & mask] << group * 2) |
                            (reverse_table_4_bits[(i >> group * 2) & mask] << group) |
                            (reverse_table_4_bits[(i >> group * 3) & mask]);
        // printf("Reverse of %lu is %lu\n", i, reverse_table_16_bits[i]);
    }

    return reverse_table_16_bits;
}


unsigned long reverse_bits(unsigned long n, const vector<unsigned long>& reverse_table)
{
    const int k_bit_mask = 0xFFFF;
    const int k_groups = 16;

    return (reverse_table[n & k_bit_mask] << k_groups * 3) |
        (reverse_table[ (n >> k_groups) & k_bit_mask ] << k_groups * 2) |
        (reverse_table[ (n >> k_groups * 2) & k_bit_mask ] << k_groups) |
        (reverse_table[ (n >> k_groups * 3) & k_bit_mask ]);
}

int main()
{
    vector<unsigned long> reverse_table = generate_reverse_table();
    assert(reverse_bits(18446744073709551615, reverse_table) == 18446744073709551615);
    assert(reverse_bits(18446744073709551614, reverse_table) == 9223372036854775807);
    return 0;
}
