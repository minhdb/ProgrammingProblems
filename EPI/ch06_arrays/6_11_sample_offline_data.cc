/**
 * EPI Chapter 06 Arrays
 *
 * This problem is motivated by the need for a company to select a random
 * subset of its customers to roll out a new feature to. For example, a social
 * networking company may want to see the effect of a new UI on page visit
 * duration without taking the chance of alienating all its users if the
 * rollout is unsuccessful.
 *
 * Implement an algorithm that takes as input an array of distinct elements
 * and a size, and returns a subset of the given size of the array elements.
 * All subsets should be equally likely. Return the result in input array
 * itself.
 *
 * Hint: How would you construct a random subset of size k + 1 given a random
 * subset of size k?
 */

#include <cstdio>
#include <vector>
#include <random>
#include <unordered_set>

using std::vector;
using std::unordered_set;

/**
 *  Brute force solution: O(nk).
 *  Randomly pick an index from vector v, add v[i] to result,
 *  and remove v[i] from v. Do this k times.
 */
vector<int> get_k_subset(vector<int>& v, int k)
{
    vector<int> res;
    
    std::default_random_engine generator((std::random_device())());
    while (k--) {
        std::uniform_int_distribution<int> dis(0, v.size()-1);
        int rand_idx = dis(generator);
        // printf("rand_idx: %d\tv.size: %zu\n", rand_idx, v.size() - 1);
        res.emplace_back(v[rand_idx]);
        v.erase(v.begin() + rand_idx);
    }

    return res;
}

/**
 * Time complexity: O(k)
 * Space complexity: O(1)
 *
 * Generate an index from [i+1..n-1] and swap it with the ith element k times.
 * The result array first k elements will have the uniformly distributed elements
 * from the old array.
 *
 * When k > n/2, we can compute the elements that we want to remove instead to avoid
 * making more than n/2 calls to uniform_int_distribution.
 */
void get_k_subset_linear(vector<int>& v, size_t k)
{
    std::default_random_engine generator((std::random_device())());
    if (k < v.size() >> 0x1) {
        for (size_t i = 0; i < k; i++) {
            std::swap(v[i], 
                v[std::uniform_int_distribution<int>(i+1, static_cast<int>(v.size() - 1))(generator)]);
        }
    } else {
        for (size_t i = 0; i < v.size() - k; i++) {
            std::swap(v[v.size() - i - 1],
                    v[std::uniform_int_distribution<int>(0, v.size() - i - 2)(generator)]);
        }
    }
}

void print_vect(const vector<int>& v, size_t k)
{
    for (size_t i = 0; i < k; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

int main()
{
    vector<int> tc{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    // print_vect(get_k_subset(tc, 7));
    get_k_subset_linear(tc, 18);
    print_vect(tc, 18);
    return 0;
}
