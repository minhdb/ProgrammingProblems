#include <iostream>

using namespace std;

int main()
{
    int height = 0;
    int N;
    cin >> N;
    
    int i = 1;
    while (N > 0) {
        height++;
        N -= (i*i);
        i += 2;
    }
    if (N < 0) height--;
    cout << height << endl;
    
    return 0;
}
