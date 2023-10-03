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
 void InitQueue(sQueue &Q){
  Q.rear=(lnode*)malloc(sizeof(lnode));
 
   Q.rear=Q.front;
   Q.rear->next=NULL;
   

 } 
 
 //链队列的入队 
 void QueueInsert(sQueue &Q,int num){
  lnode *q;
  q=(lnode*)malloc(sizeof(lnode));
  q->data=num;
  q->next=NULL;
  Q.front->next=q;
  Q.rear=q;
  free(q);

 }
 //链队列的出队 
int QueueDelete(sQueue &Q,int *num) //无元素出队时，printf个失败
{ if(Q.front==Q.rear)
  return 0;
  *num=Q.front->next->data; 
  Q.front->next=Q.front->next->next;
  return 1;
 }
 //链队列的遍历 
 void DispQueue(sQueue &Q){
 lnode *q;
  q=Q.front->next;
  for(q=Q.front->next;q!=NULL;q=q->next) 
  
  printf("%d ",q->data);
  


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
//     printf("（3）链队列出队：");
//     QueueDelete(Queue1,&num);
//     printf("出队%d ",num);
//   QueueDelete(Queue1,&num);
//     printf("出队%d \n",num);
//     printf("（5）输出链队列：");
//     DispQueue(Queue1); 
//     printf("\n");
//     printf("（6）链队列出队："); 
//     QueueDelete(Queue1,&num);printf("出队%d ",num);
//     QueueDelete(Queue1,&num);printf("出队%d ",num);
//     QueueDelete(Queue1,&num);printf("出队%d ",num);
//     QueueDelete(Queue1,&num);
 }