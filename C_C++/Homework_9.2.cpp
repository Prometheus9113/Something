#include <stdio.h>

#include <stdlib.h>

#define max_vertex_num 100 //最多顶点个数

typedef char VertexData;

typedef int AdjType ;

typedef int OtherInfo ;

 

 

typedef struct Node

{

       int adjvex;  //定义该弧指向顶点的位置

       struct Node *nextarc; //定义下一条弧上网指针

} Node;

 

typedef struct VVertexNode

{

       char data; //定义顶点的数据

       Node *firstarc;  //定义该顶点第一条弧的指针

} VertexNode[max_vertex_num];

 

typedef struct{

       VertexNode vertex;

        int vexnum,arcnum;

} AdjList;  //定义邻接表

 

int LocateVertex(AdjList  *G,VertexData v)  //求顶点的位置

{

       int j=-1,i;

       for(i=0;i<G->vexnum;i++)

            if(v==G->vertex[i].data)

                return i;

       return (j);

}

 

 

void CreateList(AdjList *G) //用邻接表创建无向图

{

        int i;

        char v1,v2;

        printf("用邻接表来创建图\n请输入图的顶点个数和弧数\n") ;

        scanf("%d%d",&G->vexnum,&G->arcnum);

        printf("请用一行输入图的各个顶点,不用逗号隔开\n");

        getchar();

        for(i=0;i<G->vexnum;i++)

    {

        scanf("%c",&G->vertex[i].data); //输入图的各个顶点

            G->vertex[i].firstarc=NULL;

    }

        printf("请用一行输入图中所有两顶点之间的弧，例如，a,b b,c b,d\n");

        int a1,a2;

        for(i=0;i<G->arcnum;i++)

        {

            getchar();

            scanf("%c,%c",&v1,&v2);

            a1=LocateVertex(G,v1);   a2=LocateVertex(G,v2);

            Node *p1,*p2;

            if(a1!=-1&&a2!=-1)
            {

                p1 =new Node;

                p1->adjvex=a2;

                p1->nextarc=G->vertex[a1].firstarc;

                G->vertex[a1].firstarc=p1;
                
                p2=new Node;

                p2->adjvex= a1;

                p2->nextarc=G->vertex[a2].firstarc;

                G->vertex[a2].firstarc=p2;
                
            }

        }

 

}

 

void print(AdjList *G)  //打印邻接表建立的图

{

int i;

printf("打印出用邻接表创建的无向图\n");

    for(i=0;i<G->vexnum;i++)

    {

        printf("%c---->",G->vertex[i].data);

        Node *t;

        t=G->vertex[i].firstarc;

        while(t!=NULL)

        {

            printf(" %c ",G->vertex[t->adjvex].data);

            t=t->nextarc;

        }

      printf("\n");

    }

}

 

 

int main()

{

       AdjList GG;

       CreateList(&GG);

       print(&GG);

       return 0;

}