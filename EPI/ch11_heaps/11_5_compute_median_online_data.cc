/**
 * EPI Chapter 11 Heaps
 *
 * 11.5 Compute the median of online data
 * You want to compute the running median of a squence of numbers. The sequence
 * is presented to you in a streaming fashion-you cannot back up to read an
 * earlier value, and you need to output the median after reading in each new
 * element. For example, if the input is
 *
 * 1, 0, 3, 5, 2, 0, 1
 *
 * the output is
 *
 * 1, 0.5, 1, 2, 2, 1.5, 1
 *
 * Design an algorithm for computing the running median of a sequence.
 *
 * Avoid looking at all values each time you read a new value.
 */

#include <queue>
#include <cassert>
#include <sstream>
#include <string>
#include <vector>

using std::priority_queue;
using std::istringstream;
using std::string;
using std::vector;

/**
 * Idea: Use min-heap to keep track of the upper half.
 * Use max-heap to keep track of the lower half.
 */
void OnlineMedian(istringstream& sequence)
{
    priority_queue<int, vector<int>> max_heap;
    priority_queue<int, vector<int>, std::greater<>> min_heap;
    int next_input;
    while (sequence >> next_input) {
        if (min_heap.empty()) {
            min_heap.emplace(next_input);
        } else {
            if (min_heap.top() <= next_input) {
                min_heap.emplace(next_input);
            } else {
                max_heap.emplace(next_input);
            }
        }
        
        // Ensure that min_heap and max_heap have the equal number of elements.
        // Or that min_heap always have 1 more element than max_heap if the
        // total number of elements is odd.
        if (max_heap.size() > min_heap.size()) {
            min_heap.emplace(max_heap.top());
            max_heap.pop();
        } else if (min_heap.size() > max_heap.size() + 1) {
            max_heap.emplace(min_heap.top());
            min_heap.pop();
        }
        // Print out the median.
        if ((max_heap.size() + min_heap.size()) % 2 == 0) {
            printf("%f\n", (max_heap.top() + min_heap.top()) / 2.0);
        } else {
            printf("%f\n", static_cast<float>(min_heap.top()));
        }
    }
}

int main()
{
    string tc1{"1 0 3 5 2 0 1"};
    istringstream tc1_iss(tc1);
    OnlineMedian(tc1_iss);
    return 0;
}
