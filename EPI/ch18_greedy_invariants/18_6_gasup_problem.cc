/**
 * EPI Chapter 18 - Greedy algorithms
 *
 * In the gasup problem, a number of cities are arranged on a circular road.
 * You need to visit all the cities and come back to the starting city. A
 * certain amount of gas is available at each city. The amount of gas summed
 * up over all cities is equal to the amount of gas required to go around the
 * road once. Your gas tank has unlimited capacity. Call a city ample if you
 * can begin at that city with an empty tank, refill at it, then travel through
 * all the remaining cities, refilling at each and return to the ample city,
 * without running out of gas at any point.
 *
 * Given an instance of the gasup problem, how would you efficiently compute an
 * ample city? You can assume that there exists an ample city.
 *
 * Hint:
 */

#include <vector>
#include <cstdio>

using std::vector;

/**
 * BF solution: Try every city. The time complexity will be O(n^2) because
 * there are n cities to try and we need to traverse at least n city to test
 * if our gas tank drops below 0. Quite inefficient because there will be
 * cities with very small amount of initial gasoline.
 *
 * Let {a, b} be a city where the cost to travel to from the previous city
 * is a and can refill b unit of gasoline.
 *
 * Time complexity: O(n^2)
 * Space complexity: O(1)
 */
int GetAmpleCityBF(vector<vector<int>>& cities)
{
    int gas_tank = 0;
    int res = -1;;
    int n = static_cast<int>(cities.size());
    for (int i = 0; i < n; i++) {
        gas_tank = cities[i][1];
        bool is_ample = true;
        int j = (i + 1) % n;

        do {
            gas_tank -= cities[j][0];
            if (gas_tank < 0) {
                is_ample = false;
                break;
            }
            gas_tank += cities[j][1];
            j = (j + 1) % n;
        } while (j != (i + 1) % n);

        if (is_ample) {
            res = i;
            break;
        }
    }
    return res;
}

/**
 * Idea: Starts at the city such that the cost of gas to that city is largest.
 * Why? We know the total of gas required to travel all cities once equals
 * the refillable gas summed at all cities. We also assume the cost and refill
 * gas are non-negative.
 *
 * Claim: To complete the final trip, which will cost most, we need to have
 * enough gas gathered along the way.
 */
int GetAmpleCity(vector<vector<int>>& cities)
{
    return 0;
}


/**
 * EPI solution:
 */

const int kMPG = 20;

// gallons[i] is the amount of gas in city i, and distances[i] is the distance
// city i to the next city.
size_t FindAmpleCity(const vector<int>& gallons, const vector<int>& distances)
{
    int remaining_gallons = 0;
    struct CityAndRemainingGas {
        int city = 0, remaining_gallons = 0;
    };

    CityAndRemainingGas city_remaining_gallons_pair;
    const int num_cities = gallons.size();
    for (int i = 1; i < num_cities; i++) {
        remaining_gallons += gallons[i - 1] - distances[i - 1] / kMPG;
        if (remaining_gallons < city_remaining_gallons_pair.remaining_gallons)
            city_remaining_gallons_pair = {i, remaining_gallons};
    }
    return city_remaining_gallons_pair.city;
}

int main()
{
    vector<vector<int>> tc1{{5, 3}, {4, 7}, {7, 6}};
    printf("%d\n", GetAmpleCityBF(tc1));

    vector<vector<int>> tc2{{3,0}, {7,0}, {1, 13}, {2, 0}};
    printf("%d\n", GetAmpleCityBF(tc2));
    return 0;
}
