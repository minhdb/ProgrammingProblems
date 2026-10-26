/**
 * UVA 11340 - New spaper
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define gc getchar_unlocked


int main() {
    int t, k, m, a; unsigned char c;
    unsigned long p;
    while(scanf("%d", &t) != EOF) {
        while(t--) {
            p = 0;
            scanf("%d", &k); int table[256]; 
            for (int i = 0; i < 256; i++)
                table[i] = 0;
            while(gc() != '\n');
            
            while(k--) {
                c = gc(); gc();
                scanf("%d", &table[c]);
                while(gc() != '\n');
            }
            
            scanf("%d", &m); gc();
            while(m--) {
                while ((c = gc()) != EOF) {
                    if (c == '\n') break;
                    p += table[c];
                }
            }    
            
            printf("%.2f$\n", p/(100.0));
        }
    }
    
    return 0;
}