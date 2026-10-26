/**
 * EPI Chapter 11 Heaps
 *
 * 11.1 Merge sorted files
 *
 * This problem is motivated by the following scenario. You are given 500
 * files, each containing stock trade information for an S&P 500 company.
 * Each trade is encoded by a line in the following format:
 * 1232111, AAPL, 30, 456.12
 *
 * The first number is the time of the trade expressed as the number of
 * milliseconds since the start of the day's trading. Lines within each file
 * are sorted in increasing order of time. The remaining values are the stock
 * symbol, number of shares, and price. You are to create a single file
 * containing all the trades from the 500 files, sorted in order of increasing
 * trade times. The individual files are of the order 5-100 MBs; the combines
 * file will be of the order of five gigabytes. In the abstract, we're trying
 * to solve the following problem.
 *
 * Write a program that takes as input a set of sorted sequences and computes
 * the union of these sequences as a sorted sequence. For example,
 * if the input is <3, 5, 7>, <0, 6>, <0, 6, 28>, then the output is
 * <0, 0, 3, 5, 6, 6, 7, 28>
 *
 * Hint: which part of each sequence is significant as the algorithm executes?
 */

#include <queue>
#include <vector>
#include <cassert>

using std::vector;
using std::priority_queue;

/**
 * BF solution: Put all elements from all sequence into an array and sort it.
 *
 * Time complexity: O(nlogn) where n is the number of elements.
 * Space complexity: O(1)
 */

/**
 * Heap solution: Use the fact that each given sequence is sorted.
 *
 * Time complexity: O(nlogk)
 * Space complexity: O(k)
 */
struct IteratorCurrentAndEnd {
    bool operator>(const IteratorCurrentAndEnd& that) const {
        return *current > *that.current;
    }

    vector<int>::const_iterator current;
    vector<int>::const_iterator end;
};

vector<int> MergeSortedArray(vector<vector<int>>& sequences)
{
    priority_queue<IteratorCurrentAndEnd, vector<IteratorCurrentAndEnd>, std::greater<>>
        min_heap;
    for (const auto& seq : sequences) {
        if (!seq.empty()) {
            min_heap.emplace(IteratorCurrentAndEnd{seq.cbegin(), seq.end()});
        }
    }

    vector<int> res;
    while (!min_heap.empty()) {
        auto smallest_array = min_heap.top();
        min_heap.pop();
        if (smallest_array.current != smallest_array.end) {
            res.emplace_back(*smallest_array.current);
            min_heap.emplace(IteratorCurrentAndEnd{std::next(smallest_array.current), smallest_array.end});
        }
    }

    return res;
}

int main()
{
    vector<vector<int>> tc1{{3, 5, 7}, {0, 6}, {0, 6, 28}};
    vector<int> tc1_res{0, 0, 3, 5, 6, 6, 7, 28};
    assert(MergeSortedArray(tc1) == tc1_res);
}
