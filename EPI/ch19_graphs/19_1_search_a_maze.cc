/**
 * EPI Chapter 19 Graphs
 *
 * 19.1 Search a maze.
 *
 * It's natural to apply graph models and algorithms to spatial problems.
 * Consider a black and white digitized image of a maze-while pixels represent
 * open areas and black spaces are walls. There are 2 special white pixels: one
 * is designated the entrance and the other is the exit. The goal in this
 * problem is to find a way of getting from the entrance to the exist, as
 * illustrated in Figure 19.5 on the next page.
 *
 * Given a 2D array of black and white entries representing a maze with
 * designated entrance and exit points, find a path from the entrance to the
 * exit, if one exists.
 *
 * Hint: Model the maze as a graph.
 */

#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>

using std::vector;
using std::string;
using std::find;

// typedef enum { WHITE, BLACK } Color;
//

enum class Color
{
    WHITE, BLACK
};

struct Coordinate
{
    bool operator==(const Coordinate& coord) const
    {
        return x == coord.x && y == coord.y;
    }

    bool operator!=(const Coordinate& coord) const
    {
        return !(*this == coord);
    }

    int x, y;
};

void PrintMaze(const vector<vector<Color>>& maze, const Coordinate& start, const Coordinate& end,
        const vector<Coordinate>& path)
{
    int n = static_cast<int>(maze.size());
    int m = static_cast<int>(maze[0].size());
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            Coordinate curr{i, j};
            if (!path.empty() 
                    && find(cbegin(path), cend(path), Coordinate{i, j}) != path.cend()
                    && curr != path.front() && curr != path.back() ) {
                printf(".");
            } else if (curr == start) {
                printf("s");
            } else if (curr == end) {
                printf("e");
            } else if (maze[i][j] == Color::WHITE) {
                printf(" ");
            } else {
                printf("#");
            }
        }
        printf("\n");
    }
}

/**
 * Check if curr is within the maze and is a white pixel.
 */
bool IsFeasible(const vector<vector<Color>>& maze, const Coordinate& curr)
{
    int m = static_cast<int>(maze.size());
    int n = static_cast<int>(maze[0].size());

    return curr.x >= 0 && curr.x < m && 
        curr.y >= 0 && curr.y < n && 
        maze[curr.x][curr.y] == Color::WHITE;
}

/**
 * Run DFS to see if it's possible to reach the destination. If it's
 * possible, return that path. Similar to backtracking.
 *
 * Choice: Visit adjacent cells horizontally and diagonally and have white
 * color.
 *
 * Constraints: Only can visit white colored cells and are in the maze.
 *
 * Goal: If we can reach a coordinate that equals Coordinate e.
 *
 * Time complexity: O(V + E).
 * Space complexity: O(E)
 */
bool SearchMazeHelper(vector<vector<Color>>& maze, vector<Coordinate>& path, const Coordinate& cur, const Coordinate& e)
{
    if ( cur == e ) {
        return true;
    }

    int direction[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

    for (int k = 0; k < 4; k++) {
        Coordinate new_move{cur.x + direction[k][0],
                            cur.y + direction[k][1]};
        if (IsFeasible(maze, new_move)) {
            maze[new_move.x][new_move.y] = Color::BLACK;
            path.emplace_back(new_move);
            if (SearchMazeHelper(maze, path, new_move, e)) {
                return true;
            }
            maze[new_move.x][new_move.y] = Color::WHITE;
            path.pop_back();
        }
    }

    return false;
}

vector<Coordinate> SearchMaze(vector<vector<Color>>& maze,
        const Coordinate& s, const Coordinate& e)
{
    vector<Coordinate> path{s};
    SearchMazeHelper(maze, path, s, e);
    return path;
}

int main()
{
    vector<vector<Color>> maze(10, vector<Color>(10, Color::WHITE));
    maze[0][0] = Color::BLACK;
    maze[0][6] = Color::BLACK;
    maze[0][7] = Color::BLACK;
    
    maze[1][2] = Color::BLACK;

    maze[2][0] = Color::BLACK;
    maze[2][2] = Color::BLACK;
    maze[2][5] = Color::BLACK;
    maze[2][6] = Color::BLACK;
    maze[2][8] = Color::BLACK;
    maze[2][9] = Color::BLACK;

    maze[3][3] = Color::BLACK;
    maze[3][4] = Color::BLACK;
    maze[3][5] = Color::BLACK;
    maze[3][8] = Color::BLACK;

    maze[4][1] = Color::BLACK;
    maze[4][2] = Color::BLACK;

    maze[5][1] = Color::BLACK;
    maze[5][2] = Color::BLACK;
    maze[5][5] = Color::BLACK;
    maze[5][7] = Color::BLACK;
    maze[5][8] = Color::BLACK;

    maze[6][5] = Color::BLACK;

    maze[7][0] = Color::BLACK;
    maze[7][2] = Color::BLACK;
    maze[7][4] = Color::BLACK;
    maze[7][6] = Color::BLACK;

    maze[8][0] = Color::BLACK;
    maze[8][2] = Color::BLACK;
    maze[8][3] = Color::BLACK;
    maze[8][7] = Color::BLACK;
    maze[8][8] = Color::BLACK;
    maze[8][9] = Color::BLACK;

    maze[9][7] = Color::BLACK;
    maze[9][8] = Color::BLACK;


    Coordinate s{9, 0}, e{0, 9};
    vector<Coordinate> found_path = SearchMaze(maze, s, e);
    PrintMaze(maze, s, e, found_path);
    return 0;
}
