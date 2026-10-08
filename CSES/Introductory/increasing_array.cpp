#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

int main()
{
    unsigned long n;
    cin >> n;
    vector<unsigned long> arr(n, 0);
    cin >> arr[0];
    unsigned long prev_element = arr[0];
    unsigned long min_moves = 0;
    for (unsigned long i = 1; i < n; i++) {
        cin >> arr[i];
        if (arr[i] < prev_element) {
            min_moves += (prev_element - arr[i]);
            arr[i] = prev_element;
        }
        prev_element = arr[i];
    }

    cout << min_moves << std::endl;

    return 0;
}
