/**
 * EPI 06/16/2021
 *
 * Write a program that takes a double x and an integer y and returns x^y.
 * If nore overflow and underflow.
 *
 * Hint: Exploit mathematical properties of exponentiation.
 */

#include <cassert>
#include <cmath>
#include <cstdio>

/**
 * Naive solution runs in O(y) where y is an int counting down.
 *
 * O(2^n) where n is the number of bits in integer types.
 */
double pow_brute_force(double x, int y)
{
    double res = x;
    if (y == 0) return 1;
    else if (y > 0) {
        while (y > 1) {
            res *= x;
            y--;
        }
    } else {
        res = 1/x;
        while (y < -1) {
            res /= x;
            y++;
        }
    }
    return res;
}

/**
 * Fast exponentiation: my solution.
 * Time complexity: O(logy)
 * Space complexity: O(logy)
 */
double pow_fast_exp(double x, int y)
{
    double res = x;
    if (y == 0) {return 1;}
    else if (y > 0) {
        if (y == 1) return x;
        return pow_fast_exp(x, y / 2) * pow_fast_exp(x, y - y/2);
    } else {
        if (y == -1) return 1/x;
        return pow_fast_exp(x, y / 2) * pow_fast_exp(x, y - y/2);
    }
    return res;
}

/**
 * Solution from EPI.
 *
 * Idea: x = (x^(y/2) )^2 iff y & 0x1 = 0.
 * x = x * x^(y/2) * x^(y/2) iff y & 0x1 = 1.
 *
 * If y is negative, let x = 1/x and y = -y.
 *
 * Time complexity: O(n) where n is the number of bits.
 */
double pow_fast_epi(double x, int y)
{
    if (y < 0) {
        x = 1/x;
        y = -y;
    }

    while (y) {
        if (y & 0x1) {
            x *= x;
        }
        x *= x;
        y >>= 0x1;
    }

    return x;
}

int main()
{
    // Test for brute force solution.
    assert(pow_brute_force(3, 1) == 3);
    assert(pow_brute_force(431, 0) == 1);
    assert(pow_brute_force(2, 10) == 1024);
    assert(pow_brute_force(2, -1) == 0.5);
    assert(pow_brute_force(2, -2) == 0.25);
    assert(pow_brute_force(2, -5) == 0.03125);

    // Test for divide and conquer solution.
    assert(pow_fast_exp(3, 1) == 3);
    assert(pow_fast_exp(431, 0) == 1);
    assert(pow_fast_exp(2, 10) == 1024);
    assert(pow_fast_exp(2, -1) == 0.5);
    assert(pow_fast_exp(2, -2) == 0.25);
    assert(pow_fast_exp(2, -5) == 0.03125);
    return 0;
}
