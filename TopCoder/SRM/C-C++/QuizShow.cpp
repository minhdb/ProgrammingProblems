#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

/*
 * TopCoder SRM 223 DIV 1 - Level One.
 * Minh Bui
 */

class QuizShow {
public:
	int wager(vector <int>, int, int);
};

int QuizShow::wager(vector <int> scores, int wager1, int wager2) {        
    int odd, best, bet;
    bet = 0; best = 0;
    for (int score = 0; score <= scores[0]; score++) {
        for (int i = -1; i < 2; i += 2)
            for (int j = -1; j < 2; j += 2)
                for (int k = -1; k < 2; k += 2) {
                    if (scores[0] + score * i > scores[1] + wager1 * j &&
                       scores[0] + score * i > scores[2] + wager2 * k) odd++;
                }
        if (odd > best) {bet = score; best = odd;}
    }
    
    return bet;
}

<%:testing-code%>
// Powered by [KawigiEdit] 2.0!