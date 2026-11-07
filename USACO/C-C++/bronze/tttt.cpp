#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <set>
#include <iostream>
using namespace std;

bool get_single_winner(const char& a, const char& b, const char& c)
{
    if (a == b && b == c) return true;
    return false;
}

pair<bool, string> get_team_winners(const char& a, const char& b, const char& c)
{
    if (a == b && c != a) {
        if (c < a)
            return make_pair(true, string{c, a});
        else
            return make_pair(true, string{a, c});
    } else if (b == c && a != b) {
        if (b < a)
            return make_pair(true, string{b, a});
        else
            return make_pair(true, string{a, b});
    } else if (a == c && a != b) {
        if (a < b)
            return make_pair(true, string{a, b});
        else
            return make_pair(true, string{b, a});
    }
    return make_pair(false, "");
}

int main()
{
    ifstream fin("tttt.in");
    ofstream fout("tttt.out");

    int n = 3;
    vector<string> grid;
    for (int i = 0; i < n; i++) {
        string cur_s;
        fin >> cur_s;
        grid.push_back(cur_s);
    }

    set<char> single_winners;
    set<string> team_winners;

    // LDiag
    bool sd = get_single_winner(grid[0][0], grid[1][1], grid[2][2]);
    if (sd) single_winners.emplace(grid[0][0]);
    else {
        auto dd = get_team_winners(grid[0][0], grid[1][1], grid[2][2]);
        if (dd.first) {
            team_winners.emplace(dd.second);
        }
    }

    // RDiag
    sd = get_single_winner(grid[0][n-1], grid[1][n-2], grid[2][n-3]);
    if (sd) single_winners.emplace(grid[0][n-1]);
    else {
        auto dd = get_team_winners(grid[0][n-1], grid[1][n-2], grid[2][n-3]);
        if (dd.first) {
            team_winners.emplace(dd.second);
        }
    }

    // Vertical
    for (int i = 0; i < n; i++) {
        sd = get_single_winner(grid[0][i], grid[1][i], grid[2][i]);
        if (sd) single_winners.emplace(grid[0][i]);
        else {
            auto dd = get_team_winners(grid[0][i], grid[1][i], grid[2][i]);
            if (dd.first) {
                team_winners.emplace(dd.second);
            }
        }
    }
    
    // Horizontal
    for (int i = 0; i < n; i++) {
        sd = get_single_winner(grid[i][0], grid[i][1], grid[i][2]);
        if (sd) single_winners.emplace(grid[i][0]);
        else {
            auto dd = get_team_winners(grid[i][0], grid[i][1], grid[i][2]);
            if (dd.first) {
                team_winners.emplace(dd.second);
            }
        }
    }

    fout << single_winners.size() << "\n" << team_winners.size() << endl;
}
