#include <stdio.h>

int main (void){
    int a;

    while (1)
    {
        scanf("%d", &a);
        if (a == 42)
        {
            break;
        }
        printf("%d\n", a);
    }
    
}
