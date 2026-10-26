/**
 * EPI Chapter 18 - Greedy algorithm
 *
 * Several applications require identification of elements in a sequence which
 * occur more than a specified fraction of the total number of elements in the
 * sequence. For example, we may want to identify the users using excessive
 * network bandwidth or IP addresses originating the most HTTP requests. Here
 * we consider a simplified version of this problem.
 *
 * You are reading a sequence of strings. You know a priori that more than half
 * the strings are repetitions of a single string (the "majority element") but
 * the positions where the majority element occurs are unknown. Write a program
 * that makes a single pass over the sequence and identifies the majority
 * element. For example, if the input is {b, a, c, a, a, b, a, a, c, a}, then a
 * is the majority element (it appears in 6 out of the 10 places).
 *
 * Hint: Take advantage of the existence of a majority element to perform
 * elimination.
 */

#include <sstream>
#include <utility>
#include <unordered_map>

using std::string;
using std::istringstream;
using std::vector;
using std::pair;
using std::unordered_map;

/**
 * Use a hash table to store the frequency of each element. Keep track of
 * the element that has the maximum frequency.
 *
 * Time complexity: O(N)
 * Space complexity: O(N)
 */
string MajoritySearchHT(istringstream& input_stream)
{
    unordered_map<string, int> m;
    string in;
    string cur_max;
    size_t max_freq = 0;
    while (input_stream >> in) {
        if (m.count(in) == 0) {
            m[in] = 0;
        } else {
            m[in]++;
            if (m[in] > max_freq) {
                max_freq = m[in];
                cur_max = in;
            }
        }
    }

    return cur_max;
}

/**
 * Idea: Exploit the hint that the frequency of the majority element is greater
 * than the total number of elements. The algorithm is only correct when the
 * property above holds.
 *
 * There are 2 groups of indices: indices that have the majority element and
 * those that don't.
 *
 * If we consider 2 consecutive elements in the stream, if they are different,
 * then there can be at most 1 out of 2 elements that might be a majority
 * element.
 *
 * We know m / n > 1 / 2, if the next element is not a majority element,
 * m / (n - 2) > 1/2.
 *
 * If the next element is a majority element,
 * (m - 1) / (n - 2) > 1/2
 *
 *
 * Time complexity: O(N)
 * Space complexity: O(1)
 */
string MajoritySearch(istringstream& input_stream)
{
    string in;
    string candidate;
    int count = 0;
    while (input_stream >> in) {
        if (count == 0) {
            candidate = in;
            count++;
        } else if (candidate == in) {
            count++;
        } else {
            count--;
        }
    }
    return candidate;
}

int main()
{
    istringstream tc1_in("b a c a a b a a c a");
    printf("%s\n", MajoritySearchHT(tc1_in).c_str());

    istringstream tc2_in("1 2 3 5 5 5 5 5");
    printf("%s\n", MajoritySearch(tc2_in).c_str());
    return 0;
}
