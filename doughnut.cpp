// 2017-08-20
#include <stdio.h>
#include <algorithm>

int main() {
    int N; scanf("%d", &N);
    for(int i = 1; i <= N; i++) {
        int c = 0, k = 0, w = 0;
        scanf("%d %d %d", &c, &k, &w);
        
        if(k >= c * w) {
            printf("yes\n");
        }
        else {
            printf("no\n");
        }
    }
}