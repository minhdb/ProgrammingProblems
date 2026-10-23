#include <iostream>
#include <unordered_map>

using namespace std;

int main()
{
    unordered_map<int, int> m;
    unsigned p;
    cin >> p;
    if (p < 3) {
        cout << "NO" << endl;
        return 0;
    }

    for (unsigned i = 1; i <= p; i++) {
        unsigned f = 0;
        cin >> f;
        m.emplace(make_pair<int, int>(i, f));
    }

    for (const auto& p : m) {
        if (m.count(p.second) != 0) {
            if (m.count(m[p.second]) != 0) {
                if (m[m[p.second]] == p.first) {
                    cout << "YES" << endl;
                    return 0;
                }
            }
        }
    }
    cout << "NO" << endl;
    return 0;
}
