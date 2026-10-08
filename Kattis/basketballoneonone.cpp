#include <iostream>
#include <string>

int main()
{
    std::string records;
    std::cin >> records;
    
    unsigned int a_points = 0;
    unsigned int b_points = 0;
    
    bool tie_flag = false;
    for (unsigned int i = 0; i < records.size(); i += 2) {
        unsigned short cur_points = records[i+1] - '0';
        if (records[i] == 'A') {
            a_points += cur_points;
            if (tie_flag && a_points >= (b_points + 2)) {
                 std::cout << "A" << std::endl;
                 return 0;
            }
        } else {
            b_points += cur_points;
            if (tie_flag && b_points >= (a_points + 2)) {
                 std::cout << "B" << std::endl;
                 return 0;
            }
        }
        
        if (a_points == b_points && a_points == 10) {
            tie_flag = true;
        } else {
            if (!tie_flag && a_points == 11) {
                std::cout << "A" << std::endl;
                return 0;
            } else if (!tie_flag && b_points == 11) {
                std::cout << "B" << std::endl;
                return 0;
            }
        }
    }

    return 0;
}
