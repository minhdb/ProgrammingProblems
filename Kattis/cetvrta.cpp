#include <iostream>

using namespace std;

int main()
{
    int x1,y1, x2,y2, x3,y3;
    cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
    int length = 0;    
    if (x1 == x2 || x2 == x3 || x3 == x1) {

        if (x1 == x2) {
            length = abs(y1-y2);
            if (y3 == min(y1,y2)) {
                cout << x3 << " " << y3 + length;
            } else {
                cout << x3 << " " << y3 - length;
            }
        }
        else if (x2 == x3) {
            length = abs(y3-y2);
            if (y1 == min(y3,y2)) {
                cout << x1 << " " << y1 + length;
            } else {
                cout << x1 << " " << y1 - length;
            }
        }
        else if (x3 == x1) {
            length = abs(y3-y1);
            if (y2 == min(y3,y1)) {
                cout << x2 << " " << y2 + length;
            } else {
                cout << x2 << " " << y2 - length;
            }
        }
        
    } else if (y1 == y2 || y2 == y3 || y3 == y1) {
        if (y1==y2) {
            length = abs(x1-x2);
            if (x3 == min(x1,x2)) {
                cout << x3 + length << " " << y3;
            } else {
                cout << x3 - length << " " << y3;
            }
        }
        else if (y2==y3) {
            length = abs(x2-x3);
            if (x1 == min(x2,x3)) {
                cout << x1 + length << " " << y1;
            } else {
                cout << x1 - length << " " << y1;
            }
        }
        else if (y3==y1) {
            length = abs(x3-x1);
            if (x2 == min(x1,x3)) {
                cout << x2 + length << " " << y2;
            } else {
                cout << x2 - length << " " << y2;
            }
        }
        
    }
    cout << endl;
    return 0;
}

