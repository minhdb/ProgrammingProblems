/**
 * EPI Chapter 05 06/21/2021
 *
 * A palindromic string is one which reads the same forwards and backwards,
 * e.g., "redivider". In this problem, you are to write a program which
 * determines if the decimal representation of an integer is a palindromic
 * string. For example, your program should return true for the inputs
 *
 * 0, 1, 7, 11, 121, 333, and 2147447412, and false for the inputs
 *
 * -1, 12, 100, and 2147483647
 *
 *  Write a program that takes an integer and determines if that integer's
 *  representation as a decimal string is a palindrome.
 *
 *  Hint: It's easy to come up with a simple expression that extracts the
 *  LSD. Can you find a simple expression for the MSD?
 */


#include <cassert>
#include <cmath>


/**
 * Quickest solution is to reverse it and check if it's the same number.
 *
 * Time complexity: O(n) where n is the number of decimal digits.
 * Space complexity: O(1)
 */

int reverse(int n)
{
    int result = 0;
    int abs_n = abs(n);

    while (abs_n) {
        result = result * 10 + abs_n % 10;
        abs_n /= 10;
    }
    
    return n < 0 ? -result : result;
}

bool is_palindrome_number_reverse_solution(int n)
{
    if ( n < 0 ) return false;
    return reverse(n) == n;
}

/**
 * Directly checks if the corresponding MSD and LSD are the same.
 *
 * Time complexity: O(n) where n is the number of decimal digits.
 * Space complexity: O(1)
 */
bool is_palindrome_number(int n)
{
    // To get the LSD: while (n) lsd = n % 10; n /= 10;
    // To get the MSD:
    // while (n)
    //  msd = n / pow(10, num_digits(x) - 1);
    //  n   = n % pow(10, num_digits(x) - 1);
    if (n < 0) return false;
    while ( n ) {
        int digits = static_cast<int>(floor(log10(n)) + 1);
        if (digits == 1) return true;
        int lsd = n % 10;
        int msd = n / static_cast<int>(pow(10, digits - 1));
        if (msd != lsd) return false;

        n /= 10;
        n %= static_cast<int>(pow(10, digits - 2));
    }
    
    return true;
}

int main()
{
    assert(is_palindrome_number_reverse_solution(333));
    assert(is_palindrome_number_reverse_solution(2147447412));
    assert(!is_palindrome_number_reverse_solution(2147483647));
    assert(!is_palindrome_number_reverse_solution(100));
    assert(!is_palindrome_number_reverse_solution(12));
    assert(!is_palindrome_number_reverse_solution(2147483647));

    assert(is_palindrome_number(333));
    assert(is_palindrome_number(2147447412));
    assert(!is_palindrome_number(2147483647));
    assert(!is_palindrome_number(100));
    assert(!is_palindrome_number(12));
    assert(!is_palindrome_number(2147483647));

    return 0;
}
