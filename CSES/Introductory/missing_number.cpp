#include <iostream>

int main()
{
    unsigned long long n;
    std::cin >> n;
    unsigned long long sum{0};
    for (unsigned int i = 0; i < n; i++) {
        unsigned int cur_var{0};
        std::cin >> cur_var;
        sum += cur_var;
    }

    std::cout << n*(n+1)/2 - sum << std::endl;
    return 0;
}
