#include    <stdio.h>
#include    <malloc.h>
#include    <stdlib.h>
#include    <windows.h>
#include    <string.h>
#include    <queue>
#include	<ctime>

#define OK 1

#define ERROR 0

#define TURE 1

#define FALSE 0

#define MAX_SIZE 100    //设定的最大容量

#define EXTRA_SIZE 10   //再申请空间时使用

#define FIRST_CLASS 1       //头等舱

#define BUSINESS_CLASS 2    //商务舱

#define ECONOMY_CLASS 3     //经济舱

#define PASSWORD 114514		//管理员密码

/*

	所有的功能函数记得都在前面重载一下哦(●'?'●)

*/



/*

===========================================================

    记得看注释！！！

    有特殊数据类型要在开头define一下，免得用混了

    头文件中有<stack>和<queue>，可以直接使用栈和队列操作

    具体用法为

    定义队列为：    std::queue<数据类型> 队列名称; 
    例： std::queue<int> q;
    q.empty()       如果队列为空返回true，非空返回false
    q.size()        返回队列中元素个数
    q.pop()         删除队首元素，但不返回其值
    q.front()       返回队首元素，但不删除该元素
    q.push()        在队尾压入新元素
    q.back()        返回队尾元素，但不删除该元素
    就不需要单独写队列的结构体了

===========================================================

*/


typedef int Status;


struct Date		//时间结构体
{

	int Year;

	int Mounth;

	int Day;

	int Minute;

	int Hour;

};

struct Passagers
{

    char name[15];  //单个旅客姓名

    int classes;    //舱位等级
    
    int  booked[3]={0,0,0}; 	//订票量

};      //旅客名单

typedef Passagers Passager;

typedef struct Node
{
	Passager passager;
	 
	Node * next; 

}Passagerlist, *point;	//购票乘客量



struct Airlinee
{
    
	char begging[20];	//起点站名

    char arrival[50];   //终点站名

    char Airlinenum[20];    //航班号

    int Airplanenum;   //飞机号

    Date date;  //飞行日期

    int passagernum[3]={0,0,0};    //成员定额
    
    int leftticketsnum[3]={0,0,0};	//余票量

	int Booked[3]={0,0,0};	//已经订票量
    
    Passagerlist *passagerlist;     //已购票乘客名单（用链表）

    std::queue <Passager> Bookingpassager;        //等候乘客名单（用队列）

};  //航线信息

typedef Airlinee Airline;

struct Airlines
{
	Airline airline[MAX_SIZE];  //所有航线 

	int num=0; //航线总数 

};

Airlines airlines;	//所有航班的查找表 

int FLAG=FALSE;			//判断是否结束程序

void PrintList(Airline airline);

void Create(Airline &airline);

Status Input(Airline &airline);

Status Search(Airline airline, int n, Status temp[]);

void InputAirlines();

void purchase();

void Order(int n);

void refund();

void PrintInformation(Airline airline);

void BackStage();

void MainMenu();

void Present();

void Delete(Airline &airline, int n);

void ChangeInformation(Airline &airline);

void LoadData();

void PrintWaitingList(Airline &airline);

Status Monitor(int n);

/*

===========================================================

            下面是功能函数部分，咱们自由发挥！

===========================================================

*/





int main()
{

	system("color F0");
	
	LoadData();		//假如有文件系统，就从文件中加载数据（这个函数暂时还没写）
	do
	{

	    MainMenu();

	}while(FLAG==FALSE);

}





void PrintList(Airline airline)    //打印乘客名单
{

	if(airline.Booked>airline.passagernum)
	{
		printf("航班人数已超员！");

		return;
	}
	Node *p=airline.passagerlist->next;
    while(p)
    {
        
        printf("姓名：%s\t",p->passager.name);  //打印乘客姓名

		printf("订票量：%d\t",p->passager.booked);

        switch (p->passager.classes)      //打印乘客舱位名
        {
            case FIRST_CLASS:{
                printf("头等舱\n");
                break;
            }

            case BUSINESS_CLASS:{
                printf("商务舱\n");
                break;
            }

            case ECONOMY_CLASS:{
                printf("经济舱\n");
                break;
            }
        
            default:{ 
                printf("暂无舱位信息\n");
                break;
            }
        }
		p=p->next;
    }
    return;

};





void Create(Airline &airline)        //录入航班基本信息，但不包括乘客具体信息！！！
{

	printf("请输入起点站：\t");

	scanf("%s",airline.begging);	//输入起点站

	printf("请输入终点站：\t");

    scanf("%s",airline.arrival);    //输入终点站

	printf("请输入航班号：\t");

    scanf("%s",airline.Airlinenum);  //输入航班号，飞机号

	printf("请输入飞机号：\t");

	scanf("%d",&airline.Airplanenum);

	printf("请输入航班日期（格式：yyyy.mm.dd）：\t");

    scanf("%d.%d.%d",&airline.date.Year,&airline.date.Mounth,&airline.date.Day);       //输入航班日期

	printf("请输入航班日期（格式：hh:mm）：\t");

	scanf("%d:%d",&airline.date.Hour,&airline.date.Minute);       					   //输入航班日期

	printf("请输入成员定额分别为头等舱，商务舱，经济舱");

	for(int i=0;i<3;i++)
    {
		scanf("%d",&airline.passagernum[i]);
		airline.leftticketsnum[i]=airline.passagernum[i];
	}   //输入成员定额
	
	airline.passagerlist=(Node *)malloc(sizeof(Node)); 
	
	airline.passagerlist->next=NULL;

	printf("创建完成！");

	getchar();

	getchar();

	system("cls");
};





Status Input(Airline &airline)        //录入乘客信息
{

    Passagerlist *p,*q=airline.passagerlist;
    
	Passager temp;

    while(q->next)

    	q=q->next;

    printf("请提供您的信息\n");

	printf("请输入您的姓名：\n");

    scanf("%s",temp.name);

	printf("请输入您想要预定的舱位：\n");

	printf("1为头等舱，2为商务舱，3为经济舱\n");

    scanf("%d",&temp.classes);

	if(temp.classes>3||temp.classes<1)
	{
		printf("输入有误，请再试一次！");
		getchar(); 
		getchar(); 
		return 1;
	}

	printf("请输入您的订票量：\n");

	scanf("%d",&temp.booked[temp.classes-1]);

	if(temp.booked[temp.classes-1]>airline.leftticketsnum[temp.classes-1])
		return ERROR;

    p=(Node *)malloc(sizeof(Node));

    p->passager=temp;

    q->next=p;

    airline.leftticketsnum[temp.classes-1] -= temp.booked[temp.classes-1];

	airline.Booked[temp.classes-1] += temp.booked[temp.classes-1];

	printf("订票成功！");

	getchar();
	getchar();

	system("cls");

	return TRUE;

};





void InputAirlines()	//在邻接表中创建所有航班信息{简易版(未使用文件)} 
{

	printf("请输入当前要录入的航班总量：");

	int num;

	scanf("%d",&num); 

	if(num+airlines.num>MAX_SIZE)
	{

		printf("总数已超上限，请退回再试");

		getchar();	getchar();

		return;

	}

	for(int i=airlines.num;i<airlines.num+num;i++)
	{
		
		printf("第%d个，共%d个\n",i-airlines.num+1,num);
		Airline temp;
		Create(airlines.airline[i]);

	}
	airlines.num=airlines.num+num;
	system("cls");
};





void purchase()  //订票业务 
{

	Status temp[airlines.num];

	Airline airline;

	std::time_t currentTime = std::time(NULL);

	std::tm* LocalTime = std::localtime(&currentTime);

	system("cls");

	printf("======================================================================\n");

	printf("欢迎进入订票窗口，航旅纵横竭诚为您服务\n");

	printf("======================================================================\n");

	printf("请输入查询方式\n1.按航班号查询\t2.按起始地查询\t3.按飞机号查询\n");

	int num=0;

	scanf("%d",&num);

	switch (num)
	{
		case 1:
		{
			printf("请输入您要查询的航班号：");

			scanf("%s",airline.Airlinenum);

			Search(airline,1,temp);

			if(temp[0]==-1)
			{
				printf("抱歉，未能找到您所需订票的航班\n");

				getchar();
				getchar();

				system("cls");

				return;
			}

		}
		break;
		case 2:
		{
			printf("请输入起始地：");

			scanf("%s",airline.begging);

			printf("请输入目的地：");

			scanf("%s",airline.arrival);

			Search(airline,2,temp);

			if(temp[0]==-1)
			{
				printf("抱歉，未能找到您所需订票的航班\n");

				getchar();
				getchar();

				system("cls");

				return;
			}
		}
		break;
		case 3:
		{
			printf("请输入您要查询的飞机号：");

			scanf("%d",&airline.Airplanenum);

			Search(airline,3,temp);

			if(temp[0]==-1)
			{
				printf("抱歉，未能找到您所需订票的航班\n");

				getchar();
				getchar();

				system("cls");

				return;
			}

		}
		break;
		default:
		{
			printf("输入有误，请重新输入！");
			getchar();
			purchase();
			return;
		}
			break;
	}

	printf("请输入序号：");

	scanf("%d",&num);

	std::tm specificTime{};
		specificTime.tm_year = airlines.airline[temp[num-1]].date.Year-1900;  // 年份是相对于1900年的偏移量，所以 122 表示 2022 年
		specificTime.tm_mon = airlines.airline[temp[num-1]].date.Mounth;    // 月份从 0 开始，所以 0 表示 1 月
   		specificTime.tm_mday = airlines.airline[temp[num-1]].date.Year;   // 日期
		specificTime.tm_hour = airlines.airline[temp[num-1]].date.Hour;  // 小时
   		specificTime.tm_min = airlines.airline[temp[num-1]].date.Minute;    // 分钟
   		specificTime.tm_sec = 0;    // 秒

	std::time_t specificTimeT = std::mktime(&specificTime);

	if (currentTime < specificTimeT) {
        
		printf("抱歉，该航班已经出发，请选择其他航班");

		system("cls");

		return;

   	} 

	printf("正在进入订票系统\n");

	int flag=0;
	
	flag=Input(airlines.airline[temp[num-1]]);

	if(!flag)
	{
		printf("不好意思，余票量不能满足您的需求，请问您是否选择候补？\n");

		printf("1.是\t2.否");

		int choose=0;

		scanf("%d",&choose);

		if(choose==1)
		{
			Passager Atemp;

			printf("请输入姓名，舱位等级以及订票量\n");

			scanf("%s",Atemp.name);

			printf("请输入舱位等级\n舱位等级：\n1：头等舱\t2：商务舱\t3：经济舱\n");

			scanf("%d",&Atemp.classes);

			if(Atemp.classes>3||Atemp.classes<1)	Atemp.classes=3;

			printf("请输入订票量\n");

			scanf("%d",&Atemp.booked[Atemp.classes-1]);

			if(Atemp.classes>3||Atemp.classes<1)
			{

				printf("输入的数字有误，请返回主菜单重新输入");
				system("cls");
				return;
			
			}
			airlines.airline[temp[num-1]].Bookingpassager.push(Atemp);
		}
		
	}
	system("cls");
};





void PrintInformation(Airline airline)	//输出信息函数
{

	printf("航线；%s - ",airline.begging);	//起点站

    printf("%s \n",airline.arrival);    //终点站

    printf("航班号：%s\t飞机号%d ",airline.Airlinenum,airline.Airplanenum);  //航班号，飞机号

    printf("航班日期：%d.%d.%d-",airline.date.Year,airline.date.Mounth,airline.date.Day);       //航班日期

	printf("%d:%d\n",airline.date.Hour,airline.date.Minute);       					   //航班日期

	printf("余票量：\n头等舱：%d\n商务舱：%d\n经济舱：%d\n",airline.leftticketsnum[0],airline.leftticketsnum[1],airline.leftticketsnum[2]);

}





void Order(int n)	//排序函数
{

	Airline temp;

	switch (n)
	{
		case 1:
		{

			for(int i=1;i<=airlines.num-1;i++)
                for(int j=0;j<airlines.num-i;j++)
                    if(strcmp(airlines.airline[j].begging,airlines.airline[j+1].begging)>0)
                    {

                        temp=airlines.airline[j];
                        airlines.airline[j]=airlines.airline[j+1];
                        airlines.airline[j+1]=temp;

                    }
			for(int i=0;i<airlines.num;i++)
				PrintInformation(airlines.airline[i]);

		} break;
		case 2:
		{

			for(int i=1;i<=airlines.num-1;i++)
                for(int j=0;j<airlines.num-i;j++)
                    if(strcmp(airlines.airline[j].arrival,airlines.airline[j+1].arrival)>0)
                    {

                        temp=airlines.airline[j];
                        airlines.airline[j]=airlines.airline[j+1];
                        airlines.airline[j+1]=temp;

                    }
			for(int i=0;i<airlines.num;i++)
				PrintInformation(airlines.airline[i]);

		} break;
		case 3:
		{

			for(int i=1;i<=airlines.num-1;i++)
                for(int j=0;j<airlines.num-i;j++)
                    if(strcmp(airlines.airline[j].Airlinenum,airlines.airline[j+1].Airlinenum)>0)
                    {

                        temp=airlines.airline[j];
                        airlines.airline[j]=airlines.airline[j+1];
                        airlines.airline[j+1]=temp;

                    }
			for(int i=0;i<airlines.num;i++)
				PrintInformation(airlines.airline[i]);
		} break;

		default:
			break;
	}

};





void Present()		//呈现所有航班的程序
{

	system("cls");

	printf("请选择你想要的航班展示方式：\n1.按照起点站顺序\t2.按终点站顺序\t3.按航班号顺序\t4.退出\n");
	
	int selection=0;
	
	scanf("%d",&selection);

	if(airlines.num==0)
	{

		printf("当前没有航班，请稍后再试！");
		
		return;

	}

	switch(selection)
	{
		case 1:
			Order(1);	
			break;
		case 2:
			Order(2);
			break;
		case 3:
			Order(3);
			break;
		default:
			break;
	}

	getchar();

};





void BackStage()	//后台系统(还没施工完)
{

	system("cls");

	int fuction=0;

	printf("=====================================================");

	printf("欢迎使用管理员系统");

	printf("=====================================================");

	printf("请输入你想要进入的系统\n1.创建航班\t2.查看航班以及所有乘客\t3.查看所有候补乘客名单\t4.修改后台信息\t5.退出\n");

	scanf("%d",&fuction);

	switch (fuction)
	{
		case 1:
			InputAirlines();
			break;
		case 2:
		{
			Present();
			getchar();
			getchar();
			BackStage();
			return;
		}	break;
		case 3:
		{

			char temp[15];

			Present();

			if(airlines.num==0)	return;
			
			printf("请输入你想查询的航班号：");

			scanf("%s",temp);

			if(airlines.num==0)
			{
				
				printf("当前无航班，请稍后再试！");
				return;
				
			}

			system("cls");

			for(int i=0;i<airlines.num;i++)
            {
            	
            	if(strcmp(temp,airlines.airline[i].Airlinenum)==0)
                    PrintWaitingList(airlines.airline[i]);
            
			}
			getchar();
   			getchar();
		    BackStage();
		}	break;
		case 4:
		{

			system("cls");

			if(airlines.num==0)
			{
				
 			    printf("当前无航班信息，请稍后再试！");
 			    getchar();
				getchar();
				BackStage();
 			    return;
				
			}

			printf("请输入你选择的功能；\n1.删除航班信息\t2.修改航班信息\t3.返回\n");

			scanf("%d",&fuction);

			switch (fuction)
			{
				case 1:
				{

					char temp[20];

					printf("请选择你想要删除的航班号：");

					scanf("%s",temp);

					for(int i=0;i<airlines.num;i++)
						if(strcmp(temp,airlines.airline[i].Airlinenum)==0)
						{
							Delete(airlines.airline[i],i);
							getchar();
							BackStage();
							return;
						}
					printf("未找到该航班，请重试");
					BackStage();
					return;

				}	break;
				case 2:
				{

					char temp[20];

					printf("请选择你想要修改信息的航班号：");

					scanf("%s",temp);

					for(int i=0;i<airlines.num;i++)
						if(strcmp(temp,airlines.airline[i].Airlinenum)==0)
						{
							ChangeInformation(airlines.airline[i]);
							getchar();
							BackStage();
							return;
						}
					printf("未找到该航班，请重试");
					getchar();
					BackStage();
					return;
				}
			
				default:
					BackStage();
					break;
			}
		}break;
		case 5:
			return;
			break;

		default:
		{
			printf("输入有误，请重新输入！");
			getchar();
			getchar();
			BackStage();
			return;
		}break;
	}

};




Status Search(Airline airline,int n,Status temp[])      //查询航线
{
	
	temp[0]=-1;
	
	if(airlines.num==0)	return ERROR;
	
	int k=0;

	switch (n)
	{
		case 1:
		{
			for(int i=0;i<airlines.num;i++)
			{	
				if(strcmp(airline.Airlinenum,airlines.airline[i].Airlinenum)==0)
				{
					temp[k]=i;
					k++;
					printf("%d:\n",k);
					PrintInformation(airlines.airline[i]);
				}
			}
		}
		break;
		case 2:
		{
			for(int i=0;i<airlines.num;i++)
			{	
				if(strcmp(airline.arrival,airlines.airline[i].arrival)==0&&strcmp(airline.begging,airlines.airline[i].begging)==0)
				{
					temp[k]=i;
					k++;
					printf("%d:\n",k);
					PrintInformation(airlines.airline[i]);
				}
			}
		}
		break;
		case 3:
		{
			for(int i=0;i<airlines.num;i++)
			{	
				if(airline.Airplanenum==airlines.airline[i].Airplanenum)
				{
					temp[k]=i;
					k++;
					printf("%d:\n",k);
					PrintInformation(airlines.airline[i]);
				}
			}
		}
		break;
		default:
			break;
	}
	printf("\tÒ»¹²%dÌõ½á¹û\n",k);
	return OK;
	
}




void refund()   //退票业务 
{
	
	system("cls");

	printf("=====================================================");

	printf("欢迎使用退票系统");

	printf("=====================================================");

	if(airlines.num==0)
	{
		getchar();
		printf("暂无航班！");
		return;
	}

	printf("请问您是否需要退票：\n 1.确定 \n 2.退出");

	int num=0;	scanf("%d",&num);

	if(num==1)
	{
		Status temp[airlines.num];

		Airline airline;

		printf("请输入航班号：");

		scanf("%s",airline.Airlinenum);

		printf("搜索结果：\n");

		Search(airline,1,temp);

		if(temp[0]==-1)
		{
			printf("未找到该航班，请再试一次！");
			getchar();
			refund();
			return;
		}

		printf("请输入你想退票的序号：");

		int choose=0;

		scanf("%d",&choose);

		std::time_t currentTime = std::time(NULL);

		std::tm* LocalTime = std::localtime(&currentTime);

		std::tm specificTime{};
		specificTime.tm_year = airlines.airline[temp[choose-1]].date.Year-1900;  // 年份是相对于1900年的偏移量，所以 122 表示 2022 年
		specificTime.tm_mon = airlines.airline[temp[choose-1]].date.Mounth;    // 月份从 0 开始，所以 0 表示 1 月
   		specificTime.tm_mday = airlines.airline[temp[choose-1]].date.Year;   // 日期
		specificTime.tm_hour = airlines.airline[temp[choose-1]].date.Hour;  // 小时
   		specificTime.tm_min = airlines.airline[temp[choose-1]].date.Minute;    // 分钟
   		specificTime.tm_sec = 0;    // 秒

		std::time_t specificTimeT = std::mktime(&specificTime);

		if (currentTime < specificTimeT){
        
			printf("抱歉，该航班已经出发,退票失败。");

			system("cls");

			return;

    	} 

		else printf("好的，准备为您退票\n");
		
		Passagerlist *p;
		p=airlines.airline[temp[choose-1]].passagerlist;
		char name[15];

		printf("请输入您的姓名：");

		scanf("%s",name);

		int flag=0;

		while(p->next)
		{
            if(strcmp(name,p->next->passager.name)==0)
            {
            	p->next=p->next->next;	flag=1;
            	p=airlines.airline[temp[choose-1]].passagerlist;
            	continue;
			}
			p=p->next;
		}
		if(flag)
		{
			airlines.airline[temp[choose-1]].leftticketsnum[p->next->passager.classes-1] += p->next->passager.booked[p->next->passager.classes-1];
			airlines.airline[temp[choose-1]].Booked[p->next->passager.classes-1] -= p->next->passager.booked[p->next->passager.classes-1];
			if(Monitor(temp[choose-1]))
				printf("有候补乘客成功得到座位！");
			printf("退票成功！");
			getchar();
		}
		else
		{
			printf("退票失败！");
			getchar();
		}
        system("cls");

	}
	else if(num==2)
	{
		return;
	}
	printf("未识别到有效指令，请重试。");
	getchar();
	refund();
};




void Delete(Airline &airline,int n)	//删除某趟航班（仅限后台使用）
{  
    if(n>=airlines.num)
	{
    	printf("暂无该航班信息。");

		return;
	} 
	else
	{
		for(int i=n;i<airlines.num-1;i++)
			airlines.airline[i]=airlines.airline[i+1];
		airlines.num--;
		printf("删除成功!");

	}
    
};





void ChangeInformation(Airline &airline)	//修改某趟航班信息
{
    printf("请选择您要修改的信息:\n 1.起点站 \n 2.终点站\n 3.航班号\n 3.飞机号\n 4.航班日期\n 5.航班日期\n6.乘客容量\n");
    
    int choose=0;
    scanf("%d",&choose);
    
	switch(choose)
	{
		case(1):
		{
			printf("请输入修改后的起点站：");
			scanf("%s",airline.begging);	//输入起点站
			
		};break;
		case(2):
		{
		     printf("请输入修改后的终点站：");
		     scanf("%s",airline.arrival);    //输入终点站
		};break;
		case(3):
		{
			printf("请输入修改后的航班号：");
		    scanf("%s",airline.Airlinenum);  //输入航班号
		};break;
		case(4):
		{
			printf("请输入修改后的飞机号：");
		    scanf("%d",&airline.Airplanenum);  //输入航飞机号
		};break;
		case(5):
		{
			printf("请输入修改后的航班日期(yyyy.mm.dd)：");
			scanf("%d.%d.%d",&airline.date.Year,&airline.date.Mounth,&airline.date.Day);       //输入航班日期
			printf("请输入修改后的航班日期(hh:mm)：");
            scanf("%d:%d",&airline.date.Hour,&airline.date.Minute);               //输入航班日期	   

		};break;
		case 6:
		{
			printf("请输入修改后的乘客容量：");
			scanf("%d %d %d",&airline.passagernum[0],&airline.passagernum[1],&airline.passagernum[2]);
		};break;
		default:
		{
			printf("对不起你的输入有误，请确保你的输入为1-5.\n");
			system("cls");
			ChangeInformation(airline);
			return;
		};
	};

};





void PrintWaitingList(Airline &airline)		//递归打印候补乘客名单
{

	if(airline.Bookingpassager.empty())
	{
		
		printf("无候补乘客\n"); 
		return;
		
	}
	
	else
	{

		Passager temp;

		temp=airline.Bookingpassager.front();

		airline.Bookingpassager.pop();

		printf("姓名：%s\t",temp.name);  //打印乘客姓名

		printf("订票量：%d\t",temp.booked);

        switch (temp.classes)      //打印乘客舱位名
        {
            case FIRST_CLASS:{
                printf("头等舱\n");
                break;
            }

            case BUSINESS_CLASS:{
                printf("商务舱\n");
                break;
            }

            case ECONOMY_CLASS:{
                printf("经济舱\n");
                break;
            }
        
            default:{ 
                printf("暂无舱位信息\n");
                break;
            }
        }

		PrintWaitingList(airline);

		airline.Bookingpassager.push(temp);

	}


};





Status Monitor(int n)
{

	if(airlines.airline[n].Bookingpassager.empty())
		return FALSE;
	else
	{
		Passager Temp;
		Temp=airlines.airline[n].Bookingpassager.front();
		if(airlines.airline[n].leftticketsnum[Temp.classes]-Temp.booked[Temp.classes]>0)
		{
			airlines.airline[n].leftticketsnum[Temp.classes] -= Temp.booked[Temp.classes];
			airlines.airline[n].Booked[Temp.classes] += Temp.booked[Temp.classes];
			Passagerlist *p,*q;
			p=airlines.airline[n].passagerlist;
			q=(Node *)malloc(sizeof(Node));
			q->passager=Temp;
			while (p->next)
			{
				p=p->next;
			}
			q->next=p->next;
			p->next=q->next;
		}
		else
			return FALSE;
		return TRUE;
	}
}
/*

	这个主菜单函数是用的上次大作业的哈，是需要进行更改的！！( ?? ω ?? )?

*/

void MainMenu()		//主菜单函数
{

    int functioNnumber;

	system("cls");
	
	printf(" 航空客运订票系统\n\n");

	for(int i=1;i<=50;i++)
		printf("=");
    
	printf("\n 1.后台管理系统\t\n");

	printf(" 2.查询以及购票\t\n");

	printf(" 3.退票\t\n");

	printf(" 4.退出该系统\t\n");

	for(int i=1;i<=50;i++)
		printf("=");

	printf("\n请选择你所需要的功能：");

	scanf("%d",&functioNnumber);

	switch(functioNnumber)
	{
		case(1):
		{
			int password=PASSWORD,temp=0;
			system("cls");
			printf("该系统为工作人员使用，请输入使用密码：");
			scanf("%d",&temp);
			if(temp==password)
			{
				system("cls");
				BackStage();
				system("cls");
				getchar();			
				printf("\n按任意键返回主菜单\n");
				getchar();
				getchar();
				MainMenu();
			}
			else
			{
				printf("密码错误！");
				getchar();
				getchar();
				system("cls");
				MainMenu();
			}
		};break;
		case(2):
		{
			system("cls");
			purchase();
			system("cls");
			getchar();
			printf("\n按任意键返回主菜单\n");
			getchar();
			getchar();
			MainMenu();
		};break;
		case(3):
		{
			system("cls");
			refund();
			system("cls");
			getchar();
			printf("\n按任意键返回主菜单\n");
			getchar();
			getchar();
			MainMenu();
		};break;
		case(4):
		{
			FLAG=TRUE;

			for(int i=1;i<=30;i++)
				printf("*");

			printf("感谢使用本系统");

			for(int i=1;i<=30;i++)
				printf("*");
        
			return;
		};break;
		default:
		{
			printf("对不起你的输入有误，请确保你的输入为1-4.\n");
			printf("按任意键返回主菜单\n");
			getchar(); 
			getchar();
			MainMenu();
		};
	};
};







/*

	完成主线任务后才可进入隐藏副本哦   :) 

*/


void LoadData()
{



};
