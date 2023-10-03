#include<stdio.h>

int main()
{
    int a=1;
    long b=2;
    short c=3;
    float d=4.0001;
    double f=8.00001;
    printf("%d\n",sizeof(a));
    printf("%d\n",sizeof(b));
    printf("%d\n",sizeof(c));
    printf("%d\n",sizeof(d));
    printf("%d",sizeof(f));
}