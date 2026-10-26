/**
 * EPI Chapter 14 Sorting
 *
 * 07/30/2021
 * 14.5 Merge intervals.
 *
 * Suppose the time during the day that a person is busy is stored as a set of
 * disjoint time intervals. If an event is added to the person's calendar, the
 * set of busy times may need to be updated.
 *
 * In the abstract, we want a way to add an interval to a set of disjoint
 * intervals and represent the new set as a set of disjoint intervals. For
 * example, if the initial set of intervals is [-4, -1], [0, 2], [3, 6],
 * [7, 9], [11, 12], [14, 17], and the added interval is [1, 8], the result
 * is [-4, 1], [0, 9], [11, 12], [14, 17].
 *
 * Write a program which takes as input an array of disjoint closed intervals
 * with integer endpoints, sorted by increasing order of left endpoint, and an
 * interval to be added, and returns the union of the interval in the array and
 * the added interval. Your result should be expressed as union of disjoint
 * intervals sorted by left endpoint.
 *
 * Hint: What's the union of 2 closed intervals?
 */

#include <vector>
#include <cassert>
#include <algorithm>

using std::min;
using std::max;
using std::vector;

struct Interval
{
    bool operator==(const Interval& i) const
    { 
        return left == i.left && right == i.right; 
    }

    int left, right;
};


/**
 * Idea of BF solution: While there are at least 2 mergable intervals, keep merging
 *
 * Time complexity:
 * Space complexity:
 */
vector<Interval> MergeIntervalsBF(const vector<Interval>& disjoint_intervals,
        Interval new_interval)
{
    vector<Interval> res;
    return res;
}

/**
 * Time complexity: O(n)
 * Space complexity: O(1)
 */
vector<Interval> MergeIntervals(const vector<Interval>& disjoint_intervals, 
        Interval new_interval)
{
    vector<Interval> res;
    size_t i = 0;

    // Process intervals in disjoint_intervals which come before new_interval.
    while ( i < disjoint_intervals.size() && 
            new_interval.left > disjoint_intervals[i].right ) {
        res.emplace_back(disjoint_intervals[i++]);
    }

    // Process intervals in disjoint_intervals which overlap with new_interval.
    while (i < disjoint_intervals.size() &&
            new_interval.right >= disjoint_intervals[i].left) {
        // If [a, b] and [c, d] overlap, their union is
        // [min(a, c), max(b, d)]
        new_interval = {min(new_interval.left, disjoint_intervals[i].left),
                        max(new_interval.right, disjoint_intervals[i].right)};
        i++;
    }

    res.emplace_back(new_interval);

    // Process intervals in disjoint_intervals which come after new_interval.
    res.insert(res.end(), disjoint_intervals.begin() + i, disjoint_intervals.end());

    return res;
}

int main()
{
    Interval i1{-4, -1};
    Interval i2{0, 2};
    Interval i3{3, 6};
    Interval i4{7, 9};
    Interval i5{11, 12};
    Interval i6{14, 17};

    vector<Interval> tc1{i1, i2, i3, i4, i5, i6};
    Interval ia{1, 8};

    // is [-4, 1], [0, 9], [11, 12], [14, 17].
    Interval i7{0, 9};
    vector<Interval> tc1_res{i1, i7, i5, i6};
    assert(MergeIntervals(tc1, ia) == tc1_res);

    return 0;
}


