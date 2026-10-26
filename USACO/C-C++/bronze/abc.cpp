/**
 * https://usaco.org/index.php?page=viewproblem2&cpid=1059
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    vector<int> n(7,0);
    for (int i = 0 ;i < 7; i++) {
        cin >> n[i];
    }

    int a = *std::min_element(n.begin(), n.end());
    n.erase(find(n.begin(), n.end(), a));
    int b = *std::min_element(n.begin(), n.end());
    n.erase(find(n.begin(), n.end(), b));
    int c = *std::max_element(n.begin(), n.end()) - a - b;
    cout << a << " " << b << " " << c << "\n";

    return 0;
}
