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



//求二叉树的双亲结点值

//参数 rightSibling 为右兄弟的值，flag为查找成功标志，flag=1,  找到右兄弟，flag=0, 未找右兄弟

void getRightSibling(BiTree T, TElemType e, TElemType &rightSibling, int &flag)

{

    if(T!=NULL)
    {

        if(T->rightchild!=NULL&&T->leftchild!=NULL)
            if(T->leftchild->data==e)
            {
                rightSibling=T->rightchild->data;
                flag=1;
                return;
            }
        getRightSibling(T->leftchild,e,rightSibling,flag);
        getRightSibling(T->rightchild,e,rightSibling,flag);

    }
    else
        return;

} 



int main()

{

    int flag=0;
    TElemType rightchild;
    BiTree T;
    char str[50],c;
    int a[50];
    scanf("%s\n",str);
    scanf("%c",&c);
    int i=0;
    while(str[i]!='\0')
    {
        a[i]=str[i];
        i++;
    }
    CreateBiTree1(T,a,i);
    i=c;
    getRightSibling(T, i, rightchild, flag);
    if(flag)
        printf("%c",rightchild);
    else
        printf("no right sibling");
    return 0;

}