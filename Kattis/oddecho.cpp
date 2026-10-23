#include <iostream>

using namespace std;

int main()
{
    int N;
    cin >> N;
    for (int i = 1; i <= N; i++) {
        string s;
        cin >> s;
        if (i % 2 == 1) cout << s << endl;
    }
    return 0;
}
