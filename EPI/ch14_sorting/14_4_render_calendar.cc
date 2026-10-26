/**
 * EPI Chapter 14 Sorting
 *
 * 07/30/2021
 *
 * 14.4 Render a calendar
 *
 * Consider the problem of designing an online calendaring applicatinon. One
 * component of the design is to render the calender, i.e., display it
 * visually.
 * Suppose each day consists of a number of events, where an event is specified
 * as a start time and a finish time. Individual events for a day are to be
 * rendered as nonoverlapping rectangular regions whose sides are parallel to
 * the X- and Y-axes.. Let the X-axis correspond to time. If an event starts at
 * time b and ends at time e, the upper and lower sides of its corresponding
 * rectangle must be at b and e, respectively.
 *
 * Suppose the Y-coordinates for each day's events must lie between 0 and L
 * ( a specified const ), and each event's rectangle must have the same
 * "height" (distance between sides parallel to the X-axis). Your task is to
 * compute the maximum height an event rectangle can have. In essence, this is
 * equivalent to the following problem
 *
 * Write a program that takes a set of events, and determines the maximum
 * number of events that take place concurrently.
 *
 * Hint: Focus on endpoints.
 */

#include <vector>
#include <cassert>
#include <algorithm>

using std::vector;
using std::sort;

struct Event
{
    int start;
    int end;
};

struct EndPoint
{
    bool operator<(const EndPoint& e) const {
        // If times are equal, an endpoint that starts an interval comes first.
        return time != e.time ? time < e.time : (isStart && !e.isStart);
    }

    int time;
    bool isStart;
};

/**
 * BF solution: For each event's endpoint, count the number of events that
 * contain it.
 *
 * Observation: The number of events scheduled changes only at times are at the
 * start or end of an event.
 *
 * Time complexity: O(n^2)
 * Space complexity: O(1)
 */
int FindMaxConcurrentEventBF(const vector<Event>& A)
{
    int max_events = 0;

    for (size_t i = 0; i < A.size(); i++) {
        int count_events = 1;
        for (size_t j = i + 1; j < A.size(); j++) {
            if (A[i].end >= A[j].start && A[i].end <= A[j].end)
                count_events++;
        }

        max_events = std::max(max_events, count_events);
    }
    
    return max_events;
}

/**
 * Idea: Build an array of 2n points. Sort the points based on the time with
 * starting points coming first.
 *
 * Time complexity: O(nlogn)
 * Space complexity: O(n)
 */
int FindMaxConcurrentEventEPI(const vector<Event>& A)
{
    // Build an array of all endpoints.
    vector<EndPoint> E;
    for (const Event& e : A) {
        E.emplace_back(EndPoint{e.start, true});
        E.emplace_back(EndPoint{e.end, false});
    }

    // Sorts the endpoint array according to the time, breaking ties by putting
    // start times before end times.
    sort(E.begin(), E.end());

    // Track the number of simultaneous events, and record the maximum number
    // of simultaneous events.
    int max_num_simultaneous_events = 0, num_simultaneous_events = 0;
    for (const EndPoint& ep : E) {
        if (ep.isStart) {
            num_simultaneous_events++;
            max_num_simultaneous_events = std::max(num_simultaneous_events, max_num_simultaneous_events);
        } else {
            num_simultaneous_events--;
        }
    }
    return max_num_simultaneous_events;
}

/**
 * Variant: Users 1, 2, ..., n share an Internet connection. User i uses b_i
 * bandwidth from times s_i to f_i inclusive. What's the peak bandwidth usage?
 */

int main()
{
    Event e1 = {1, 5};
    Event e2 = {6, 10};
    Event e3 = {11, 13};
    Event e4 = {14, 15};
    Event e5 = {2, 7};
    Event e6 = {8, 9};
    Event e7 = {12, 15};
    Event e8 = {4, 5};
    Event e9 = {9, 17};
    vector<Event> tc1{e1, e2, e3, e4, e5, e6, e7, e8, e9};
    // assert(FindMaxConcurrentEventEPI(tc1) == 3);
    assert(FindMaxConcurrentEventBF(tc1) == 3);
    return 0;
}
