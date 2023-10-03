#include<stdio.h>

#include<stdlib.h>

 

typedef enum

{

    False,

    True

}Bool;

 

typedef struct Node

{

       int data;

       struct Node *lchild;

       struct Node *rchild;

}NODE,*BSTree;

/*

在指针pTree所指的二叉排序树中递归查找关键字为key的元素，

若查找成功，则返回指向该元素节点的指针，否则返回NULL

*/

 

BSTree search(BSTree pTree,int key)

{

    if(pTree->data==key)    return pTree;
    
    else if(pTree->data>key&&pTree->lchild!=NULL)
        
        return search(pTree->lchild,key);
    
    else if(pTree->rchild!=NULL)

        return search(pTree->rchild,key);

    return NULL;

}

 

Bool search_BSTree(BSTree pTree,int key,BSTree parent,BSTree &p)

{

       if(!pTree)         //如果pTree为NULL，则查找不成功                                                                                  

       {     //这里包含了树空，即pTree为NULL的情况

              p = parent;

              return False;

       }

       else             //否则，继续查找

       {                                                     

              if(key == pTree->data)                    //如果相等，则查找成功                                  

              {

                     p = pTree;

                     return True;

              }

              else if(key < pTree->data)        //在左子树中递归查找

                     return search_BSTree(pTree->lchild,key,pTree,p);   

              else                                           //在右子树中递归查找

                     return search_BSTree(pTree->rchild,key,pTree,p);

    }

}

/*

递归中序遍历二叉排序树，得到元素从小到大有序排列的序列

*/

 

void in_traverse(BSTree pTree)

{

       if(pTree)

       {

              if(pTree->lchild)

                     in_traverse(pTree->lchild);

              printf("%d ",pTree->data);

              if(pTree->rchild)

                     in_traverse(pTree->rchild);      

       }

}

 

Bool insert(BSTree &pTree,int key)

{

       BSTree p,s;

       if(!search_BSTree(pTree,key,NULL,p))              //如果查找失败，则执行插入操作

       {

        s=(BSTree)malloc(sizeof(BSTree));      //为新节点分配空间，并对各域赋值
        
        s->data=key;    s->lchild=s->rchild=NULL; 

        if(!p)  pTree=s;

        else if(p->data>key)    p->lchild=s;

        else    p->rchild=s;

        return True;

       }

       else

            return False;

}

/*

根据所给的长为len的arr数组，按数组中元素的顺序构建一棵二叉排序树

*/

 

BSTree create_BSTree(int *arr,int len)

{

       BSTree pTree = NULL;

       int i;

       //按顺序逐个节点插入到二叉排序树中

       for(i=0;i<len;i++)

              insert(pTree,arr[i]);

       return pTree;

}

 

int main()

{

       int i;

       int num;

       int key;

       int *arr;

       BSTree pTree;

       printf("请输入节点个数：\n");

       scanf("%d",&num);

 

       //输入num个整数

       arr = (int *)malloc(num*sizeof(int));

       printf("请依次输入这%d个整数（必须互不相等）：\n",num);

       for(i=0;i<num;i++)

              scanf("%d",arr+i);

 

       //中序遍历该二叉排序树，使数据按照从小到大的顺序输出

       pTree = create_BSTree(arr,num);

       printf("中序遍历该二叉排序树的结果：");

       in_traverse(pTree);

       printf("\n");

 

       //查找给定的整数

      

       printf("请输入要查找的整数：\n");

       scanf("%d",&key);

       if(search(pTree,key))

              printf("查找成功\n");

       else

              printf("查找不到该整数\n");

       return 0;

}