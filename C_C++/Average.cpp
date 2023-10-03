#include <stdio.h>
#include <math.h>


double ava(double a[],int n)
{
    double e=0;
    for(int i=0;i<n;i++)
        e=e+a[i];
    e=e/n;
    return e;
}


double average(double a[],int n)
{

    double sum=0,aver;
    aver=ava(a,n);
    for(int i=0;i<n;i++)
        sum=sum+(a[i]-aver)*(a[i]-aver);
    sum=sum/n;
    sum=sqrt(sum);
    printf("标准差为 %lf\n",sum);
    return sum;
}

int main()
{
    int n;
    scanf("%d",&n);
    if(n<=4)
        return 0;
    double a[n];
    for(int i=0;i<n;i++)
        scanf("%lf",&a[i]);
    double Sx=average(a,n);
    double c[12]={1.65,1.73,1.80,1.86,1.92,1.96,2.03,2.24,2.39,2.49,2.58,2.81};
    double aver;
    aver=ava(a,n);
    printf("平均值为 %lf\n",aver);
    if(n>=5&&n<=10)
        for(int i=4;i<n;i++)
            if(abs(a[i]-aver)>c[i-4]*Sx)
                printf("(%d)为坏值:%lf\n",i+1,a[i]);
    if(n>=5&&n<=12)
    for(int i=10;i<n;i++)
        if(abs(a[i]-aver)>c[7]*Sx)
            printf("(%d)为坏值:%lf\n",i+1,a[i]);
    if(n>=5&&n<=20)
        for(int i=12;i<n;i++)
            if(abs(a[i]-aver)>c[8]*Sx)
                printf("(%d)为坏值:%lf\n",i+1,a[i]);
    if(n>=5&&n<=30)
        for(int i=20;i<n;i++)
            if(abs(a[i]-aver)>c[9]*Sx)
                printf("(%d)为坏值:%lf\n",i+1,a[i]);
    if(n>=5&&n<=40)
        for(int i=30;i<n;i++)
            if(abs(a[i]-aver)>c[10]*Sx)
                printf("(%d)为坏值:%lf\n",i+1,a[i]);
    if(n>=5&&n<=50)
        for(int i=40;i<n;i++)
            if(abs(a[i]-aver)>c[11]*Sx)
                printf("(%d)为坏值:%lf\n",i+1,a[i]);
    if(n>=5&&n<=100)
        for(int i=50;i<n;i++)
            if(abs(a[i]-aver)>c[12]*Sx)
                printf("(%d)为坏值:%lf\n",i+1,a[i]);
    else
        printf("ERROR");
    return 0;

}