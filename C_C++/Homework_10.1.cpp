#include <stdio.h>

#include <stdio.h>

 

 

//打印二分查找过程的中间位置mid所对应的数字，使用printf("%d\t", midVal)

 

int Search (int a[], int n, int key){

    int low=0,high=n-1,mid;
    while(low<=high){

        mid=(low+high)/2;
        printf("%d\t",a[mid]);
        if(key==a[mid]) return mid;
        else if(a[mid]>key) high=mid-1;
        else    low=mid+1;

    }
    return 0;

}

 

int main(){

    int i, val, ret;

    int a[15]={5,10,11,15,17,19,21,25,36,38,50,51,55,57,68};

    for(i=0;i<15;i++)
        printf("%d\t", a[i]);

    printf("\n请输入所要查找的元素：");

    scanf("%d",&val);

    ret=Search(a,15,val);

    if(ret==0)
        printf("查找失败\n");

    else
        printf("查找成功\n");

       return 0;

}