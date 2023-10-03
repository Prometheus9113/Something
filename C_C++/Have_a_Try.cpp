#include <iostream>
#include <stdlib.h>

typedef int status;

#define OK 1

#define ERROR 0

#define TRUE 1

#define FALSE 0

typedef struct
{
    char *base;
    char *top;
    int length;
}Stack,*LinkedStack;

status InitStack(LinkedStack S)
{

    char *p;
    p=(char *)malloc(sizeof(char));
    if(!p)  return ERROR;
    S->base=S->top=p;
    S->length=0;
    return OK;

}

status CreatStack(LinkedStack S)
{

    char c;

}