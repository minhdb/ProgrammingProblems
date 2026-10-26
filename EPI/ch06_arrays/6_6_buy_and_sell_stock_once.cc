/**
 * EPI Chapter 06 Arrays
 *
 * Buy and sell a stock once.
 *
 * Write a program that takes an array denoting the daily stock price, and
 * returns the maximum profit that could be made by buying and then selling
 * one share of that stock.
 *
 * Hint: Identifying the minimum and maximum is not enough since the minimum
 * may appear after the maximum height. Focus on valid differences.
 */

#include <vector>
#include <cassert>
#include <cstdio>

using std::vector;

int max_profit(const vector<int>& v, vector<int>& res)
{
    int max_profit = v[1] - v[0];
    res[0] = 0;
    res[1] = 1;

    int min_price = v[0];
    int min_index = 0;

    for (size_t i = 1; i < v.size(); i++) {
        if (v[i] < min_price) {
            min_price = v[i];
            min_index = i;
        } else {
            if (max_profit < (v[i] - min_price)) {
                max_profit = v[i] - min_price;
                res[1] = i;
                res[0] = min_index;
            }
        }
    }

    printf("Max profit: %d\tBuy at: %d\tSell at: %d\n", max_profit, v[res[0]], v[res[1]]);
    return max_profit;
}

int max_profit_brute_force(const vector<int> & v, vector<int>& res)
{
    int max_profit = v[1] - v[0];
    res[0] = 0;
    res[1] = 1;

    for (size_t i = 0; i < v.size(); i++) {
        for (size_t j = i + 1; j < v.size(); j++) {
            if (v[j] - v[i] > max_profit) {
                max_profit = v[j] - v[i];
                res[0] = i;
                res[1] = j;
            }
        }
    }
    // printf("Max profit: %d\tBuy at: %d\tSell at: %d\n", max_profit, v[res[0]], v[res[1]]);
    return max_profit;
}

int main()
{
    vector<int> tc1{310, 315, 275, 295, 260, 270, 290, 230, 255, 250};
    vector<int> tc1_res(2);
    vector<int> tc1_res_sol{4, 6};
    assert(max_profit_brute_force(tc1, tc1_res) == 30);
    assert(tc1_res_sol == tc1_res);
    assert(max_profit(tc1, tc1_res) == 30);
    assert(tc1_res_sol == tc1_res);

    vector<int> tc2{9, 1, 3, 4};
    vector<int> tc2_res(2);
    vector<int> tc2_res_sol{1, 3};
    assert(max_profit_brute_force(tc2, tc2_res) == 3);
    assert(tc2_res_sol == tc2_res);
    assert(max_profit(tc2, tc2_res) == 3);
    assert(tc2_res_sol == tc2_res);

    return 0;
}
