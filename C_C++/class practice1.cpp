#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define null 0
#define OK 1
#define ERROR 0

  typedef struct node{
      int data;
      struct node *next;
  }lnode;
 
 
  typedef struct{
     lnode *front;
	 lnode *rear;
 }sQueue;


 //链队列的初始
 void InitQueue(sQueue &Q)
 {

    node *p;
    p=(node *)malloc(sizeof(node));
    if(!p)  exit(0);
    p->next=NULL;
    Q.front=Q.rear=p;

 } 
 
 //链队列的入队 
 void QueueInsert(sQueue &Q,int num)
 {
 	
    node *p;
    p=(node *)malloc(sizeof(node));
    if(!p)  exit(0);
    p->data=num;
    p->next=NULL;
    Q.rear->next=p;
    Q.rear=p;

 }
 //链队列的出队 
int QueueDelete(sQueue &Q,int *num) //无元素出队时，printf个失败
{
	
    if(Q.front->next==NULL)
    {
        printf("失败");
        Q.rear=Q.front;
        return OK;
    }


    node *p;
    p=Q.front->next;
    *num=p->data;
    Q.front->next=p->next;
    free(p);
    p=NULL;
    return OK;

}
 //链队列的遍历 
void DispQueue(sQueue &Q)
{

    if (Q.front==Q.rear)    exit(0);
    
    node *p;
    p=Q.front->next;
    while(p)
    {
        printf("%d ",p->data);
        p=p->next;
    }

} 
 
 int main(){
     sQueue Queue1;
     int num;
     InitQueue(Queue1);
     
     printf("链队列的基本操作：\n");
     printf("（1）创建链队列\n");
     QueueInsert(Queue1,1); 
     QueueInsert(Queue1,2);
     QueueInsert(Queue1,3); 
     QueueInsert(Queue1,4);
     QueueInsert(Queue1,5);
     printf("（2）输出链队列：");
     DispQueue(Queue1);
     printf("\n");
    printf("（3）链队列出队：");
    QueueDelete(Queue1,&num);
     printf("出队%d ",num);
   QueueDelete(Queue1,&num);
     printf("出队%d \n",num);
     printf("（5）输出链队列：");
     DispQueue(Queue1); 
     printf("\n");
     printf("（6）链队列出队："); 
     QueueDelete(Queue1,&num);printf("出队%d ",num);
     QueueDelete(Queue1,&num);printf("出队%d ",num);
     QueueDelete(Queue1,&num);printf("出队%d ",num);
     QueueDelete(Queue1,&num);
}

