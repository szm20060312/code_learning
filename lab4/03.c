#include <stdio.h>

int main(){
    char a='F';
    for(int i=0;i<6;i++){
        for(int j=0;j<=i;j++){
            printf("%c",a-j);
        }
        printf("\n");
    }
}