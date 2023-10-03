#include<stdio.h>

#include<malloc.h>



#define OK 1

#define ERROR 0

#define MAX_SIZE 100


typedef int TElemType;



typedef int Status;


typedef struct
{

    TElemType *base;

    TElemType *top;
    
    int stacksize;

}Sqstack;



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

Status InitStack(Sqstack &S)    //建立栈
{

    S.base=(TElemType *)malloc(MAX_SIZE*sizeof(TElemType));
    if(!S.base) return ERROR;
    S.top=S.base;
    S.stacksize=MAX_SIZE;
    return OK;

}

Status Push(Sqstack &S, TElemType e)  //入栈
{

    if(S.top-S.base>MAX_SIZE)   return ERROR;
    *S.top=e;
    S.top++;
    return OK;

}

Status Pop(Sqstack &S, TElemType &e) //出栈
{

    if(S.base==S.top)   return ERROR;
    e=*(S.top-1);
    S.top--;
    return OK;

}

Status IsEmpty(Sqstack S)
{

    if(S.base==S.top)
        return 1;
    else
        return 0;

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

Sqstack Stack;

void PrintStack(Sqstack S)
{

    TElemType a;
    if(IsEmpty(S))
    {

        return;

    }
    else
    {

        Pop(S,a);
        PrintStack(S);
        printf("%c",a);

    }

}

// 打印从根结点到叶子结点的所有路径

void printAllPaths(BiTree T)

{

    TElemType e;
    if(T!=NULL)
    {

        Push(Stack,T->data);
        if(T->leftchild!=NULL&&T->rightchild==NULL)
        {
            printAllPaths(T->leftchild);
            Pop(Stack,e);
        }
        else if(T->leftchild==NULL&&T->rightchild!=NULL)
        {
            printAllPaths(T->rightchild);
            Pop(Stack,e);
        }
        else if(T->leftchild!=NULL&&T->rightchild!=NULL)
        {
            printAllPaths(T->leftchild);
            Pop(Stack,e);
            printAllPaths(T->rightchild);
            Pop(Stack,e);
        }
        else
        {
            PrintStack(Stack);
            printf("\n");
        }

    }


} 



int main()

{

    InitStack(Stack);
    char str[50];
    int a[50];
    BiTree T;
    scanf("%s",str);
    int i=0;
    while(str[i]!='\0')
    {
        a[i]=str[i];
        i++;
    }
    CreateBiTree1(T,a,i);
    printAllPaths(T);
    return 0;

}