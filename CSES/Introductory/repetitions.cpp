#include <iostream>
#include <string>

int main()
{
    std::string s;
    std::cin >> s;
    if (s.size() == 1) {
        std::cout << 1 << std::endl;
    } else {
        unsigned int max_len = 1;
        unsigned int idx = 0;
        unsigned int jdx = 1;
        while (jdx < s.size()) {
            if (s[jdx] == s[idx]) {
                if (max_len < jdx - idx + 1) {
                    max_len = jdx - idx + 1;
                }
            } else {
                idx = jdx;
            }
            jdx++;
        }
        std::cout << max_len << std::endl;
    }

    return 0;
}
