#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>
#define gc getchar_unlocked

/*
 * UVA 10141 - Request for Proposal.
 * Minh Bui
 */

int main() {
    int n, r, i, number, j, p;
    char proposal[90], good[90], c;
    double price, comp, goodPrice;
    number = 1;
    while (scanf("%d %d", &n, &p), n || p) {
        if (number > 1) printf("\n");
        while(gc() != '\n'); 
        j = n;
        while(j--) { while ((c = gc()) != '\n'); }
        comp = -1; goodPrice = pow(2, sizeof(float) * 8);
        while (p--) {
            i = 0;
            while ((c = gc()) != '\n') { proposal[i] = c; i++; }
            proposal[i] = '\0';
            scanf("%lf %d", &price, &r);

            while((c = gc() != '\n'));
            if (comp <= (r / (n * 1.0))) {
                if (std::abs(comp - (r / (n * 1.0))) < 0.00001) {
                    if (price < goodPrice) { 
                        goodPrice = price;
                        strcpy(good, proposal);
                    }
                }
                else {
                    goodPrice = price;
                    comp = (r / (n * 1.0));
                    strcpy(good, proposal);
                }

            }
            while(r--) { while ((c = gc()) != '\n');}
        }
        printf("RFP #%d\n", number);
        printf("%s\n", good);
        number++;
    }
    return 0;
}
