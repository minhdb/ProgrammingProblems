#include <iostream>
#include <vector>

int main()
{
    unsigned long long n;
    std::cin >> n;
    std::vector<unsigned long long> results{};
    results.emplace_back(n);
    while (n != 1) {
        if (n % 2 == 0) {
            n /= 2;
        } else {
            n = (3*n + 1);
        }
        results.emplace_back(n);
    }

    for (auto& result : results) {
        std::cout << result << " ";
    }
    return 0;
}
