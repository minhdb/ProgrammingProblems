/**
 * https://usaco.org/index.php?page=viewproblem2&cpid=939
 */

#include <fstream>
#include <vector>
#include <queue>
#include <deque>
using namespace std;

bool is_valid_location(int x, int y, const vector<string>& farm, const deque<deque<bool>>& visited)
{
    if (x < 0 || x >= static_cast<int>(farm.size())) return false;
    if (y < 0 || y >= static_cast<int>(farm[x].size())) return false;
    if (farm[x][y] == 'R') return false;
    if (visited[x][y]) return false;
    return true;
}

int bfs(const vector<string>& farm) {
    int b_r = 0, b_c = 0, l_r = 0, l_c = 0;
    for (size_t i = 0; i < farm.size(); i++) {
        for (size_t j = 0; j < farm[i].size(); j++) {
            if (farm[i][j] == 'B') {
                b_r = i; b_c = j;
            } else if (farm[i][j] == 'L') {
                l_r = i; l_c = j;
            }
        }
    }

    deque<deque<bool>> visited;
    for (size_t i = 0; i < farm.size(); i++) {
        deque<bool> cur_row(false, farm[i].size());
        visited.push_back(cur_row);
    }

    queue<pair<pair<int, int>, int>> q;
    q.emplace(make_pair(make_pair(b_r, b_c), 0));
    while (!q.empty()) {
        auto cur_location = q.front();
        q.pop();
        int x = cur_location.first.first;
        int y = cur_location.first.second;
        int d = cur_location.second;
        visited[x][y] = true;
        if (x == l_r && y == l_c) {
            return d-1;
        }
        if (is_valid_location(x-1, y, farm, visited)) q.emplace(make_pair(make_pair(x-1, y), d+1));
        if (is_valid_location(x+1, y, farm, visited)) q.emplace(make_pair(make_pair(x+1, y), d+1));
        if (is_valid_location(x, y-1, farm, visited)) q.emplace(make_pair(make_pair(x, y-1), d+1));
        if (is_valid_location(x, y+1, farm, visited)) q.emplace(make_pair(make_pair(x, y+1), d+1));
    }
    return -1;
}

int main()
{
    ifstream fin("buckets.in");
    ofstream fout("buckets.out");
    vector<string> farm;
    farm.reserve(10);
    for (int i = 0; i < 10; i++) {
        string cur_row;
        fin >> cur_row;
        farm.push_back(cur_row);
    }
    fout << bfs(farm) << endl;
    return 0;
}
