#include <iostream>

int main()
{
    unsigned int s, v1, v2, t1, t2;
    std::cin >> s >> v1 >> v2 >> t1 >> t2;
    unsigned int submission_time1 = s * v1 + 2 * t1;
    unsigned int submission_time2 = s * v2 + 2 * t2;
    if (submission_time1 > submission_time2) {
        std::cout << "Second" << std::endl;
    } else if (submission_time1 < submission_time2) {
        std::cout << "First" << std::endl;
    } else {
        std::cout << "Friendship" << std::endl;
    }
    return 0;
}
