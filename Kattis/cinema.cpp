#include <iostream>

using namespace std;

int main()
{
    int N, M;
    cin >> N >> M;

    int denied = 0;
    for (int i = 0; i < M; i++) {
        int num;
        cin >> num;
        if (N - num < 0) {
            denied += (M - i);
            break;
        } else {
            N -= num;
        }
    }
    
    cout << denied << endl;
    
    return 0;
}
