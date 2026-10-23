#include <iostream>
#include <string>

using namespace std;

struct Point
{
    int x;
    int y;
};

unsigned int min_coins()
{
    string moves;
    cin >> moves;
    Point fafa{0, 0};
    Point prev{-1, -1};
    Point prev_prev{-1, -1};
    unsigned int silver_coins = 0;

    for (const char& c : moves) {
        if (c == 'U') {
            fafa.y += 1;
            prev_prev.x = prev.x;
            prev_prev.y = prev.y;
            prev.x = fafa.x;
            prev.y = fafa.y - 1;
            if (prev.x == prev.y && prev.x != -1
                && prev_prev.y < prev_prev.x) {
                silver_coins += 1;
            }
        } else if (c == 'R') {
            fafa.x += 1;
            prev_prev.x = prev.x;
            prev_prev.y = prev.y;
            prev.x = fafa.x - 1;
            prev.y = fafa.y;

            if (prev.x == prev.y && prev.x != -1
                && prev_prev.x < prev_prev.y) { 
                silver_coins += 1;
            }
        }
    }
    return silver_coins;
}

int main()
{
    unsigned int n;
    cin >> n;
    cout << min_coins() << endl;
    return 0;
}
