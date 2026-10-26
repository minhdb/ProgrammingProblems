/**
 * EPI Chapter 11 Heaps
 *
 * 07/20/2021
 *
 * Compute the k closest stars
 *
 * Consider a coordinate system for the Milky Way, in which Earth is at
 * (0, 0, 0). Model stars as points, and assume distances are in light years.
 * The milky Way consists of approximately 10^12 stars, and their coordinates
 * are stored in a file.
 *
 * How would you compute the k stars which are closest to Earth?
 *
 * Hint: Suppose you know the k closest stars in the first n stars. If the
 * (n + 1)th star is to be added to the set of k closest stars, which element
 * in that set should be evicted?
 */

#include <vector>
#include <queue>
#include <cmath>
#include <cstdio>
#include <cassert>

using std::priority_queue;
using std::vector;

void PrintVect(const vector<vector<float>>& v)
{
    for (const auto& e : v)
        printf("%f %f %f\n", e[0], e[1], e[2]);
}

/**
 * We want to find the k stars that are closest to Earth (0, 0, 0).
 * For each star in the stars collection, we add that star to our max_heap
 * priority queue. We're using max_heap here because supposed we already have
 * k closest stars out of n stars, we want to add the (n+1)th star. If the
 * distance from the (n+1)th star to Earth is smaller than the distance from
 * Earth to the farthest kth star in the max_heap, we evict this star and add
 * that (n+1)th star to the heap.
 *
 * Time complexity: O(nlogk) because we need to process all n stars and
 *  reheapifying takes O(logk).
 * Space complexity: O(k) because the heap size is only k.
 */
struct StarAndDistance
{
    bool operator<(const StarAndDistance& another_star) const
    {
        return d < another_star.d;
    }

    vector<float> coordinate;
    float d;
};

float get_dist(const vector<float>& star)
{
    return std::sqrt(star[0] * star[0] + star[1] * star[1] + star[2] * star[2]);
}

vector<vector<float>> k_closest_stars(vector<vector<float>>& stars, int k)
{
    priority_queue<StarAndDistance, vector<StarAndDistance>, std::less<>>
        max_heap;

    for (const auto& star : stars) {
        float cur_d = get_dist(star);
        if (max_heap.size() < k) {
            max_heap.emplace(StarAndDistance{star, cur_d});
        } else {
            StarAndDistance cur_farthest = max_heap.top();
            if (cur_farthest.d > cur_d) {
                max_heap.pop();
                max_heap.emplace(StarAndDistance{star, cur_d});
            }
        }
    }

    vector<vector<float>> res;
    while (!max_heap.empty()) {
        res.emplace_back(max_heap.top().coordinate);
        max_heap.pop();
    }

    PrintVect(res);
    return res;
}

int main()
{
    vector<vector<float>> tc1{
        {1.0f, 1.0f, 1.0f},
        {2.0f, 2.0f, 2.0f},
        {3.0f, 3.0f, 3.0f},
        {4.0f, 4.0f, 4.0f},
        {5.0f, 5.0f, 5.0f},
        {6.0f, 6.0f, 6.0f},
        {0.5f, 0.5f, 0.5f}
    };

    vector<vector<float>> tc1_res{
        {2.0f, 2.0f, 2.0f},
        {1.0f, 1.0f, 1.0f},
        {0.5f, 0.5f, 0.5f}
    };

    assert(k_closest_stars(tc1, 3) == tc1_res);
    return 0;
}


