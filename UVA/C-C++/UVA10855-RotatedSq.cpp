/**
 * UVA 10855 Rotated Square
 */

#include <stdio.h>
#include <stdlib.h>

char** transpose(char** c, int s) {
    char** r = (char**) malloc(s * sizeof(char*));
    int i, j;
    for (i = 0; i < s; i++) {
        r[i] = (char*) malloc(s * sizeof(char*));
        for (j = 0; j < s; j++) 
            r[i][j] = c[j][i];
        
    }
    return r;
}

void reverse_row(char* row, int s) {
    int i, j; char temp;
    i = 0; j = s - 1;
    while (i < j) {
        temp = row[i];
        row[i] = row[j];
        row[j] = temp;
        i++; j--;
    }
}

char** rotate(char** c, int s) {
    char ** t; int i;
    t = transpose(c, s);
    for (i = 0; i < s; i++) 
        reverse_row(t[i], s);
    
    return t;
}

void printGrid(char** b, int N) {
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) 
            printf("%c", b[i][j]);
            
        printf("\n");
    }
}

int count(char** grid1, char** grid2, int N, int n) {
    int c; bool s = true;
    int i, j, a, b, p, q, k; c = k = 0;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            p = i; 
            for (a = 0; a < n; a++) {
                q = j;
                for (b = 0; b < n; b++) {
                    if ((p >= N) || (q >= N)) break;
                    if (grid2[a][b] == grid1[p][q]) {
                        q++; k++;
                    } else break;
                }
                p++;
            }
            if (k == n * n) c++;
            k = 0;
        }
    }
    
    return (c);
}

int main() {
    int N, n, i, j;
    char c;
    while(scanf("%d %d", &N, &n), n || N != 0) {
        char** b = (char**) malloc(N * sizeof(char*));
        char** s = (char**) malloc(n * sizeof(char*));
        scanf("%c", &c);

        for (i = 0; i < N; i++) {
            b[i] = (char*) malloc(N * sizeof(char*));
            for (j = 0; j < N; j++) { 
                scanf("%c", &b[i][j]);
            }
            scanf("%c", &c);
        }
        
        for (i = 0; i < n; i++) {
            s[i] = (char*) malloc(n * sizeof(char*));
            for (j = 0; j < n; j++) {
                scanf("%c", &s[i][j]);
            }
            scanf("%c", &c);
        }
        
        char **r = s; 
        for (i = 0; i < 4; i++) {
            // printGrid(r, n);
            if (i < 3) printf("%d ", count(b, r, N, n));
            else printf("%d\n", count(b, r, N, n));
            r = rotate(r, n);
        }
    }
    
    return 0; 
}
