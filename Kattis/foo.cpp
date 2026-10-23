#include <bits/stdc++.h>
#include <format>

using namespace std;

using ll = long long;

int main()
{
    cout << format("Integer division -5/3: {}", -5/3) << endl;
    cout << format("Floor(-5/3): {}", floor(-5.0/3.0)) << endl;
    cout << format("Ceil(-5/3): {}", ceil(-5.0/3.0)) << endl;

    cout << format("Integer division 5/3: {}" , 5/3) << endl;
    cout << format("Floor(5/3): {}", floor(5.0/3.0)) << endl;
    cout << format("Ceil(5/3): {}", ceil(5.0/3.0)) << endl;

    int a = 3, b = 4;
    cout << format("{} == {}: {}", a, b, a == b) << endl;
    cout << format("{} != {}: {}", a, b, a != b) << endl;
    cout << format("{} > {}: {}", a, b, a > b) << endl;

    int d = -3, c = 5;
    cout << format("{} mod {}: {}", d, c, (d+c) % c) << endl;

    return 0;
}

