// 2017-08-20
#include <stdio.h>

int main() {
    while(true)  {
        int n = 0;
        scanf("%d", &n);
        
        if(n == 42) {
            return 0;
        }

        printf("%d\n", n);
    }
}