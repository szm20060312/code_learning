#include <stdio.h>

int main() {
    int a[10]={1,2,3,4,5,6,7,8,9,10};
    printf("The array is: ");

    for(int i=0;i<10;i++){
        printf("%d ",a[i]);
    }
    printf("\n");
    //int len=sizeof(a)/sizeof(a[0]);
    int len1=sizeof(a);
    int len2=sizeof(a[0]);
    // printf("The length of the array is: %d\n",len1);
    // printf("The length of each element is: %d\n",len2);
    printf("The length of the array is: %d\n",len1/len2);

    //pointer
    int *p=a;
    printf("The pointer is: %p\n",p);
    printf("The value of the first element is: %d\n",*p);
    p++;
    printf("The value of the second element is: %d\n",*p);
    
    int num=10;
    int *p2=&num;
    printf("The pointer of a variable is: %p\n",p2);
    printf("The value of the variable is: %d\n",*p2);
    return 0;
}