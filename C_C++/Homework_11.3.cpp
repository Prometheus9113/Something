#include<stdio.h>

#include<stdlib.h>

#include<string.h>

 

 

#define STUDENT_NUMBER 5//排序对象个数

 

#define NAME_ASCEND    0//按姓名递增(非递减）顺序排序

#define NUMBER_ASCEND  1//按学号递增(非递减）顺序排序

#define SCORE_ASCEND   2//按成绩递增(非递减）顺序排序

 

struct STUDENT_STRU

{

    char name[10];//姓名

    char num[6];  //学号

    int score;    //成绩

};

 

 

//按成绩分块函数

int PartitionScore(STUDENT_STRU a[], int low, int high)

{

    STUDENT_STRU key=a[low];
    STUDENT_STRU temp;
    while (low<high)
    {
        
        while(low<high&&a[high].score>=key.score)    high--;
        temp=a[high];   a[high]=a[low]; a[low]=temp;
        while(low<high&&a[low].score<=key.score)     low++;
        temp=a[high];   a[high]=a[low]; a[low]=temp;

    }
    return low;

}

 

//按姓名分块函数

int PartitionName(STUDENT_STRU a[], int low, int high)

{

    STUDENT_STRU key=a[low];
    STUDENT_STRU temp;
    while (low<high)
    {
        
        while(low<high&&strcmp(a[high].name,key.name)>=0)    high--;
        temp=a[high];   a[high]=a[low]; a[low]=temp;
        while(low<high&&strcmp(a[low].name,key.name)<=0)     low++;
        temp=a[high];   a[high]=a[low]; a[low]=temp;

    }
    return low;

}

 

//按学号分块函数

int PartitionNum(STUDENT_STRU a[], int low, int high)

{

    STUDENT_STRU key=a[low];
    STUDENT_STRU temp;
    while (low<high)
    {
        
        while(low<high&&strcmp(a[high].num,key.num)>=0)    high--;
        temp=a[high];   a[high]=a[low]; a[low]=temp;
        while(low<high&&strcmp(a[low].num,key.num)<=0)     low++;
        temp=a[high];   a[high]=a[low]; a[low]=temp;

    }
    return low;

}

 

 

void QSort(STUDENT_STRU a[], int low, int high,int sortNum)

{

switch (sortNum)

       {

              case NAME_ASCEND:

              {

                     if (low < high)

                     {

                            int pivotloc = PartitionName(a, low, high);

                            QSort(a, low, pivotloc-1, NAME_ASCEND);

                            QSort(a, pivotloc+1, high, NAME_ASCEND);

                     }

 

                     break;

              }

                    

 

              case NUMBER_ASCEND:

              {

                     if (low < high)

                     {

                            int pivotloc = PartitionNum(a, low, high);

                            QSort(a, low, pivotloc-1, NUMBER_ASCEND);

                            QSort(a, pivotloc+1, high, NUMBER_ASCEND);

                     }

 

                     break;

              }

 

              case SCORE_ASCEND:

              {

                     if (low < high)

                     {

                            int pivotloc = PartitionScore(a, low, high);

                            QSort(a, low, pivotloc-1, SCORE_ASCEND);

                            QSort(a, pivotloc+1, high, SCORE_ASCEND);

                     }

 

                     break;

              }

 

              default:

                     break;

       }// end of switch()

}

 

//主函数中定义学生结构体数组信息，并调用排序算法进行排序，每次排序后打印结果进行比对

//注意每一次排序都是在上一次排序结果（而非原始数据）的基础上进行的

int main(void)

{

    int i;

 

    STUDENT_STRU StudentStru[STUDENT_NUMBER] =

    {

        {"James", "00007", 85},

        {"Amy",   "00010", 90},

        {"Zoe",   "00001", 60},

        {"Tom",   "00005", 85},

        {"Tom",   "00015", 70},

    };//学生信息的结构体数组，注意有学生的姓名/成绩是相同的，仔细体会排序算法的稳定性

 

    //打印排序对象

    printf("初始数据为：\n");

    for (i = 0; i < STUDENT_NUMBER; i++)

    {

 

        printf("%s %s %d\n", StudentStru[i].name, StudentStru[i].num, StudentStru[i].score);

    }

 

    //姓名非递减（递增）排序

    QSort(StudentStru, 0, STUDENT_NUMBER-1, NAME_ASCEND);

    //打印排序结果

    printf("姓名非递减（递增）排序后数据：\n");

    for (i = 0; i < STUDENT_NUMBER; i++)

    {

 

        printf("%s %s %d\n", StudentStru[i].name, StudentStru[i].num, StudentStru[i].score);

    }

 

       //学号递增排序

    QSort(StudentStru, 0, STUDENT_NUMBER-1, NUMBER_ASCEND);

    //打印排序结果

    printf("学号递增排序后数据：\n");

    for (i = 0; i < STUDENT_NUMBER; i++)

    {

 

        printf("%s %s %d\n", StudentStru[i].name, StudentStru[i].num, StudentStru[i].score);

    }

 

       //成绩非递减（递增）排序

       QSort(StudentStru, 0, STUDENT_NUMBER-1, SCORE_ASCEND);

    //打印排序结果

    printf("成绩非递减（递增）排序后数据：\n");

    for (i = 0; i < STUDENT_NUMBER; i++)

    {

 

        printf("%s %s %d\n", StudentStru[i].name, StudentStru[i].num, StudentStru[i].score);

    }

       return 0;

}