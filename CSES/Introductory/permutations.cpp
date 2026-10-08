#include <iostream>

void print_beautiful_permutation(unsigned int n)
{
    if (n == 1) {
        std::cout << 1 << std::endl;
    } else if (n == 4) {
        std::cout << "2 4 1 3" << std::endl;
    } else if (n > 4) {
        unsigned int i = 2;
        do {
            std::cout << i << " ";
            i += 2;
        } while (i <= n);

        i = 1;
        do {
            std::cout << i << " ";
            i+= 2;
        } while (i <= n);
    } else {
        std::cout << "NO SOLUTION" << std::endl;
    }
}

int main()
{
    unsigned int n;
    std::cin >> n;
    print_beautiful_permutation(n);
    return 0;
}
