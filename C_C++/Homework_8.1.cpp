#include <stdio.h>

#include <string.h>

#include<malloc.h>

typedef struct node         //二叉树结点类型的定义

{    

char data;

        struct node *lchild;      //定义结点的左孩子指针

        struct node *rchild;      //定义结点的右孩子指针

} BinTNode;                       

 

BinTNode *CreateBinTree()  //输入二叉树的先序遍历序列，创建二叉链表

{  

        BinTNode *t;

        char ch;

        ch=getchar();

       if (ch=='0')             //如果读入0，创建空树

              t=NULL;

        else

        {   

                if(!(t=(BinTNode *)malloc(sizeof(BinTNode))))       return 0;

                t->data=ch;
                
                t->lchild= CreateBinTree();

                t->rchild= CreateBinTree();

        }

 

    return t;

}

 

void ListBinTree(BinTNode *t)                  //用广义表表示二叉树

{

        if (t!=NULL)

        {

              printf("%c",t->data);                //打印数据

              if (t->lchild!=NULL||t->rchild!=NULL)

              {

                     printf("(");                      //打印广义表的左括号

                     ListBinTree(t->lchild);           //用广义表表示左子树

                     if (t->rchild!=NULL)

                     printf(",");                    //打印左子树和右子树之间的逗号

                     ListBinTree(t->rchild);         //用广义表表示右子树

                     printf(")");                    //打印广义表的右括号

              }

        }

}

 

int preorder(BinTNode *t)   //对二叉树进行先序遍历  注意: 课件中的Visit(T->data)在此

//处是 printf("%3c",t->data),下同。

{

        if(t==NULL)     return 0;
        printf("%3c",t->data);
        preorder(t->lchild);
        preorder(t->rchild);
        return 0;

}

 

int inorder(BinTNode *t) //对二叉树进行中序遍历

{

        if(t==NULL)     return 0;
        inorder(t->lchild);
        printf("%3c",t->data);
        inorder(t->rchild);
        return 0;
}

 

int postorder(BinTNode *t) //对二叉树进行后序遍历

{

        if(t==NULL)     return 0;
        postorder(t->lchild);
        postorder(t->rchild);
        printf("%3c",t->data);
        return 0;

}

 

int Height(BinTNode *t)//节点深度

{

        int m,n;
        if(t==NULL)     return 0;
        else
        {
                m= Height(t->lchild);

                n= Height(t->rchild);

                if(m > n)

                        return (m + 1);
                else

                        return (n + 1);
        }

 

}

 

 

//二叉树的总结点数

int Size(BinTNode *t) 
{

        if(t==NULL)    return 0;

        else    return Size(t->lchild)+Size(t->rchild)+1;

}

 

//二叉树的叶子结点数

int Leaf(BinTNode *t) 
{

        if(t==NULL)     return 0;

        if(t->lchild==NULL&&t->rchild==NULL)
                return 1;
        return Leaf(t->lchild)+Leaf(t->rchild);

}

 

//二叉树的最大值

char Max(BinTNode *t) {

  if (t == NULL) return 0;

  if (t->lchild == NULL && t->rchild == NULL)

    return t->data;

  int l = Max(t->lchild);

  int r = Max(t->rchild);

  return l > r ? l : r;

}

 

int main()

{

        BinTNode *t=NULL;

        //int TreeHeight;

        printf("请输入先序序列,虚结点用0表示：\n");

        t=CreateBinTree();

        printf("广义表表示的二叉树的输出：\n");

        ListBinTree(t);                          //调用二叉树的广义表表示函数

        printf("\n二叉树的前序遍历结果为:\n");

        preorder(t);                             //调用二叉树先序遍历函数

        printf("\n二叉树的中序遍历结果为:\n");

        inorder(t);                              //调用二叉树中序遍历函数

        printf("\n二叉树的后序遍历结果为:\n");

        postorder(t);                            //调用二叉树后序遍历函数

        printf("\n");  

        printf("二叉树的高度为：%d\n", Height(t));

        printf("二叉树的总结点数为：%d\n", Size(t));

        printf("二叉树的叶子结点数为：%d\n", Leaf(t));

        printf("二叉树的最大值为：%c\n", Max(t));

        return 0;

}