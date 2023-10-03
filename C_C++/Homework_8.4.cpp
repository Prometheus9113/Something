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

Status CreateBiTree1(BiTree &T, int a[], int n)

{

    if(count==n)    return 0;
    if(a[count]==35)   {T=NULL;   count++;}
    else
    {
        if(!(T=(TNode *)malloc(sizeof(TNode)))) return 0;
        T->data=a[count];
        count++;
        CreateBiTree1(T->leftchild,a,n);
        CreateBiTree1(T->rightchild,a,n);
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

            if(T->leftchild!=NULL)
            {

                printf(",");

                PrintBiTree(T->rightchild);

                printf(")");

            }

        }

    }

}



//求二叉树的最大层次

//参数maxlevel 返回二叉树的最大层次

void maxLevel(BiTree T, int level, int &MaxLevel)

{

    if(T!=NULL)
    {

        level++;
        if(T->leftchild==NULL&&T->rightchild==NULL)
        {
            if(MaxLevel<level)
                MaxLevel=level;
            return;
        }
        maxLevel(T->leftchild, level, MaxLevel);
        maxLevel(T->rightchild, level, MaxLevel);

    }
    else
        return;

} 



int main()

{

    BiTree T;
    int level=0,temp=0;
    char str[50];
    int a[50];
    scanf("%s",str);
    int i=0;
    while(str[i]!='\0')
    {
        a[i]=str[i];
        i++;
    }
    CreateBiTree1(T,a,i);
    maxLevel(T,temp,level);
    printf("%d",level);
    return OK;

}