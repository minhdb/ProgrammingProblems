#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    string t;
    cin >> t;
    int n;
    cin >> n;
    vector<string> vocabs;
    while(n--) {
        string cur;
        cin >> cur;
        if (cur == t) {
            cout << "YES\n";
            return 0;
        }
        vocabs.push_back(cur);
    }

    for (size_t i = 0; i < vocabs.size(); i++) {
        if (t[0] == vocabs[i][1] && t[1] == vocabs[i][0]) {
            cout << "YES\n";
            return 0;
        }
        if (vocabs[i][1] == t[0]) {
            for (size_t j = 0; j < vocabs.size(); j++) {
                if (vocabs[j][0] == t[1]) {
                    cout << "YES\n";
                    return 0;
                }
            }
        }
    }
    cout << "NO\n";
    return 0;
}
