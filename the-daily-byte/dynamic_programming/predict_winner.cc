/**
 * The Daily Byte
 *
 * 07/22/2021
 *
 * You are given an integer array nums. 2 players are playing a game with this
 * array: player 1 and player.
 *
 * Player 1 and player 2 take turns, with player 1 starting first. Both
 * players start the game with a score of 0. At each turn, the player takes
 * one of the numbers from either end of the array (i.e. nums[0] or
 * nums[nums.length - 1]) which reduces the size of the array by 1. The player
 * adds the chose number to their score. The game ends when there are no more
 * elements in the array.
 *
 * Return true if Player 1 can win the game. If the scores of both players are
 * equal, then player 1 is still the winner, and you should also return true.
 * You may assume that both players are playing optimally.
 */

#include <vector>
#include <cassert>

using std::vector;

/**
 * List of approaches:
 *
 * 1. Recursion / backtracking.
 * 2. Minimax
 * 3. DP 2D / 1D
 */
bool playerOneWins(const vector<int>& arr)
{
    return false;
}

int main()
{
    vector<int> tc1{1, 5, 2};
    vector<int> tc2{1, 5, 233, 7};
    vector<int> tc3{3, 5, 3};
    vector<int> tc4{9, 11, 2};
    vector<int> tc5{1, 2, 3};

    assert(!playerOneWins(tc1));
    assert(playerOneWins(tc2));
    assert(playerOneWins(tc3));
    assert(playerOneWins(tc4));
    assert(playerOneWins(tc5));
    return 0;
}
