#include<stdio.h>

#include<malloc.h>



#define OK 1

#define ERROR 0



typedef int TElemType;



typedef int Status;



typedef struct Tnode{

TElemType data;

struct Tnode *leftchild;

struct Tnode *rightchild;

}TNode, *BiTree;  



//根据先序扩展序列构建二叉链表

//a[ ]为先序扩展序列数组，n为数组长度

//

int count=0;

Status CreateBiTree(BiTree &T, int a[], int n)

{

    if(count==n)    return 0;
    if(a[count]==10)   {T=NULL;   count++;}
    else
    {
        if(!(T=(TNode *)malloc(sizeof(TNode)))) return 0;
        T->data=a[count];
        count++;
        CreateBiTree(T->leftchild,a,n);
        CreateBiTree(T->rightchild,a,n);
    }
    return OK;

} 



//打印二叉树

void PrintBiTree(BiTree T)

{

    if(T!=NULL)
    {
        printf("%c",T->data);

        if(T->leftchild!=NULL||T->rightchild!=NULL)
        {
            printf("(");

            PrintBiTree(T->leftchild);

            if (T->rightchild!=NULL)
            {

                printf(",");

                PrintBiTree(T->rightchild);

                printf(")");

            }
            
        }
    }

}



//求二叉树的所有路径的数字之和

//参数totalSum为所有路径的总和

void sumofAllPaths(BiTree T, int sum, int &totalSum)

{

    if(T!=NULL)
    {

        sum=sum*10+T->data;
        if(T->leftchild==NULL&&T->rightchild==NULL)
            totalSum=totalSum+sum;
        else
        {

            sumofAllPaths(T->leftchild,sum,totalSum);
            sumofAllPaths(T->rightchild,sum,totalSum);

        }
    }
    else
        return;

}



int main()

{

    int sum=0,temp=0;
    BiTree T;
    char str[50];
    int a[50];
    scanf("%s",str);
    int i=0;
    while(str[i]!='\0')
    {
        if(str[i]=='#')
            a[i]=10;
        else
            a[i]=str[i]-48;
        i++;
    }
    CreateBiTree(T,a,i);
    sumofAllPaths(T,temp,sum);
    printf("%d",sum);

}