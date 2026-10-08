#include <iostream>
#include <string>
#include <algorithm>

using std::string;
using std::cin;
using std::cout;
using std::endl;

int main()
{
    string file_name;
    cin >> file_name;
    string extension;
    for (int i = file_name.size() - 1; i >= 0; i--) {
        extension.push_back(file_name[i]);
        if (file_name[i] == '.') {
            break;
        }
    }
    std::reverse(extension.begin(), extension.end());
    cout << extension << endl;
    return 0;
}
