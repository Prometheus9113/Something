#include <stdio.h>
#include <ctime>

void A(int &a)
{
    a++;

}

int main() {
    int a[5]={1,2,3,4,5};
    for(int i=0;i<5;i++)
        A(a[i]);

    printf("%d %d %d %d %d ",a[0],a[1],a[2],a[3],a[4]);
}
