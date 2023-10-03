#include <stdio.h>

double counting(int n)
{

    double x;
    if(n==1||n==0)
        x=1;
    
    else
        x=n*counting(n-1);
    return x;

}

double square(double x, int n)
{

    double sum=x;
    while(n!=1)
    {
        sum=sum*x;
        n--;
    }
    return sum;

}

double trangle_counting1 (double x, int n)
{

    double number;
    if(n==1)
        number=x;
    else
    {
        if(n%2==0)
            number=-square(x,2*n+1)/counting(2*n+1);

        else
            number=square(x,2*n+1)/counting(2*n+1);

        number=number+trangle_counting1(x,n-1);
    }
    return number;

}
double trangle_counting2 (double x, int n)
{

    double number;
    if(n==1)
        number=x;
    else
    {
        if(n%2==0)
            number=-square(x,2*n)/counting(2*n);

        else
            number=square(x,2*n)/counting(2*n);

        number=number+trangle_counting2(x,n-1);
    }
    return number;

}


int main()
{
    double n,number;
    int i,flag=0;
    scanf("%lf %d",&n,&i);
    if(n<0)
    {
        n=-n;
        flag=1;
    }
        
    while(n>3.1415926*2)
    {
        n-3.1415926*2;
    }


    printf("%lf",number);
}