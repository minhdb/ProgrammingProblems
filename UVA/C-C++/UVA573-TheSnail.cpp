#include <stdio.h>
#include <cmath>

/*
 * UVA 573 - The Snail
 * Minh Bui
 */

int main() {
    int h, u, d, f, c;
    double factor, height, climbed;
    while(scanf("%d %d %d %d", &h, &u, &d, &f), h && u) {
        c = 1; factor = f/100.0; height = 0;
        do {
            if (c == 1) climbed = u;
            else climbed = u -  factor * u * (c - 1);
            if (climbed > 0) height += climbed;
            if (height > h) break;
            height -= d;
            c++;
        } while (height >= 0);

        if (height <= 0) printf("failure on day %d\n", c - 1);
        else printf("success on day %d\n", c);
    }
    return 0;
}
