#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define FALSE 0 
#define TRUE 1

void mainmenu(void); 		//主菜单函数
void InputMessage(void);	//输入信息函数
void ShowMessage(void); 	//显示信息函数
void SearchMessage(void);	//查询信息函数
void searchbynumber();		//根据班次号查询函数
void searchbyaddress();		//根据终点站查询的函数
void TicketManagement(void);//选择订票/退票的函数
void TicketOrder();			//订票实现函数
void TicketDelete();		//退票实现函数
void LoadData();			//加载已经有的数据信息 
void RefreshData();				//刷新数据 

int FLAG;					//标志
int count=0;				//班次数量 


struct time					//时间结构体
{
	int hour;
	int minutes;
};
struct ticket				//车票的结构体
{
	int carnumber;		//车次
	struct time setout;
	char beginpoint[20];//起点站
	char endpoint[20];	//终点站
	float lasttime;		//行车时间
	int fixnumber;		//额定载量
	int fixednumber;	//已定票的人数
}car[100];


int main()
{
	system("color F0");
	int FLAG=FALSE;
	LoadData();
	do
	{
	mainmenu();
	}while(FLAG=FALSE);
}

void LoadData()
{
	char s[300],c;
	FILE *fp;
	int i=1,j,k=0,lines=0,number1=0,number2=0;
	if((fp=fopen("班次信息.txt","a+"))==NULL)
	{
			printf("Can not open the file!");
			exit(0);
	}
	rewind(fp);
	while((c=fgetc(fp))!=EOF)
	{
		if(c=='\n')
		lines++;
	}		//统计文件行数 
	count=lines-1;
	rewind(fp);
	for(j=0;j<lines;j++)
	{
		car[j].fixnumber=0;	car[j].fixednumber=0;
		fgets(s,200,fp);
		if(s[0]=='\0')
			count=count;
		else
		{
			if(s[1]=='\t')
				car[j].carnumber=s[0]-48;
			else
			{
				car[j].carnumber=(s[0]-48)*10+s[1]-48;	i=2;
			}
			while(s[i]=='\t')
				i++;		//跳过空格 
			if(s[i+1]==':')
			{
				car[j].setout.hour=s[i]-48;
				car[j].setout.minutes=(s[i+2]-48)*10+s[i+3]-48;
				i=i+4;
			}
			else
			{
				car[j].setout.hour=(s[i]-48)*10+s[i+1]-48;
				car[j].setout.minutes=(s[i+3]-48)*10+s[i+4]-48;
				i=i+5;
			}	//载入出发时间信息 
			while(s[i]=='\t')
				i++;		//跳过空格 
			while(s[i]!='\t')
			{
				car[j].beginpoint[k]=s[i];
				i++;	k++;
			}	k=0;	//载入起点站信息 
			while(s[i]=='\t')
				i++;		//跳过空格 
			while(s[i]!='\t')
			{
				car[j].endpoint[k]=s[i];
				i++;	k++;
			}	k=0;		//载入终点站信息 
			while(s[i]=='\t')
				i++;		//跳过空格 
			if(s[i+3]=='\t')
			{
				car[j].lasttime=s[i]-48+(s[i+2]-48)*0.1;
				i=i+3;		//载入持续时间信息 
			}
			else
			{
				car[j].lasttime=(s[i]-48)*10+s[i+1]-48+(s[i+3]-48)*0.1;
				i=i+4;		//载入持续时间信息
			} 
			while(s[i]=='\t')
				i++;		//跳过空格 
			while(s[i]!='\t')
			{
				i++;	number1++;
			}		//载入额定载量信息 
			for(k=number1;k>0;k--)
				car[j].fixnumber=car[j].fixnumber*10+s[i-k]-48;
			while(s[i]=='\t')
				i++;		//跳过空格 
			while(s[i]!='\t'&&s[i]!='\n')
			{
				i++;	number2++;
			}		//载入已订票人数信息 
			for(k=number2;k>0;k--)
				car[j].fixednumber=car[j].fixednumber*10+s[i-k]-48;
			for(k=0;k<strlen(s);k++)
				s[k]='\0';	i=1;	k=0;	number1=number2=0;	//清除缓存字符串
		}
	}	
	count++; 
}

void mainmenu()
{
	int i,functioNnumber;
	printf(" 车票管理系统\n\n");
	for(i=1;i<=50;i++)
		printf("=");
	printf("\n 1.录入班次信息\t\n");
	printf(" 2.浏览班次信息\t\n");
	printf(" 3.查询行车路线\t\n");
	printf(" 4.售票与退票系统\t\n");
	printf(" 5.退出该系统\t\n");
	for(i=1;i<=50;i++)
		printf("=");
	printf("\n请选择你所需要的功能：");
	scanf("%d",&functioNnumber);
	switch(functioNnumber)
	{
		case(1):
		{
			system("cls");InputMessage();			
			printf("\n按任意键返回主菜单\n");
			getchar();
			getchar();
			mainmenu();
		};break;
		case(2):
		{
			system("cls");ShowMessage();
			printf("\n按任意键返回主菜单\n");
			getchar();
			getchar();
			mainmenu();
		};break;
		case(3):
		{
			system("cls");SearchMessage();
			printf("\n按任意键返回主菜单\n");
			getchar();
			getchar();
			mainmenu();
		};break;
		case(4):
		{
			system("cls");TicketManagement();
			printf("\n按任意键返回主菜单\n");
			getchar();
			getchar();
			mainmenu();
		};break;
		case(5):
		{
			FLAG=TRUE;
			for(i=1;i<=30;i++)
				printf("*");
			printf("感谢使用本系统");
			for(i=1;i<=30;i++)
				printf("*");
			exit(0);
		};break;
		default:
		{
		printf("对不起你的输入有误，请确保你的输入为1-5.\n");
		printf("按任意键返回主菜单\n");
		getchar(); 
		getchar();
		mainmenu();
		};
	};
	FLAG=FALSE;
}
void InputMessage()
{
	FILE *fp;
	if((fp=fopen("班次信息.txt","a+"))==NULL)
	{
		printf("Can not open the file!");
		exit(0);
	}

	printf("请输入班次号：(1-99)\n");
	scanf("%d",&car[count].carnumber);
	fprintf(fp,"%d\t",car[count].carnumber);

	printf("请输入发车时间：\n");
	scanf("%d:%d",&car[count].setout.hour,&car[count].setout.minutes);
	if(car[count].setout.minutes>=0&&car[count].setout.minutes<=9)
		fprintf(fp,"%d:0%d\t",car[count].setout.hour,car[count].setout.minutes);
	else
		fprintf(fp,"%d:%d\t",car[count].setout.hour,car[count].setout.minutes);

	printf("请输入起点站：\n");
	scanf("%s",car[count].beginpoint);
	fprintf(fp,"%s\t",car[count].beginpoint);

	printf("请输入终点站：\n");
	scanf("%s",car[count].endpoint);
	fprintf(fp,"%s\t",car[count].endpoint);

	printf("请输入行车时间(小时)：(0.0-99.9)\n");
	scanf("%f",&car[count].lasttime);
	fprintf(fp,"%.1f\t",car[count].lasttime);

	printf("请输入额定载量：\n");
	scanf("%d",&car[count].fixnumber);
	fprintf(fp,"%d\t",car[count].fixnumber);

	printf("请输入已定票人数：\n");
	scanf("%d",&car[count].fixednumber);
	fprintf(fp,"%d\n",car[count].fixednumber); 

	printf("班次 发车时间 起点 终点 行车时间(小时) 额定载量 已订票人数\n");
	if(car[count].setout.minutes>=0&&car[count].setout.minutes<=9)
		printf("%d\t%d:0%d\t",car[count].carnumber,car[count].setout.hour,car[count].setout.minutes);
	else
		printf("%d\t%d:%d\t",car[count].carnumber,car[count].setout.hour,car[count].setout.minutes);
	printf("%s\t%s\t%.1f\t%d\t%d\t\n",car[count].beginpoint,car[count].endpoint,car[count].lasttime,car[count].fixnumber,car[count].fixednumber);
	count++;	//记录目前的班次数
}
void ShowMessage()
{
	FILE *fp;
	if((fp=fopen("班次信息.txt","r"))==NULL)
	{
		printf("Can not open the file!");
		exit(0);
	}
	printf("班次 发车时间 起点 终点 行车时间(小时) 额定载量 已订票人数\n");
	int i;
	time_t tval;
	struct tm*now;
	tval=time(NULL);
	now=localtime(&tval);
	for(i=0;i<count;i++)
	{
		if((now->tm_hour==car[i].setout.hour&&now->tm_min<car[i].setout.minutes)||(now->tm_hour<car[i].setout.hour))
		{
			if(car[i].setout.minutes>=0&&car[i].setout.minutes<=9)
				printf("%d\t%d:0%d\t",car[i].carnumber,car[i].setout.hour,car[i].setout.minutes);
			else
				printf("%d\t%d:%d\t",car[i].carnumber,car[i].setout.hour,car[i].setout.minutes);
			printf("%s\t%s\t%.1f\t%d\t%d\t\n",car[i].beginpoint,car[i].endpoint,car[i].lasttime,car[i].fixnumber,car[i].fixednumber);
		}
		else 
		{
			if(car[i].setout.minutes>=0&&car[i].setout.minutes<=9)
				printf("%d\t%d:0%d\t",car[i].carnumber,car[i].setout.hour,car[i].setout.minutes);
			else
				printf("%d\t%d:%d\t",car[i].carnumber,car[i].setout.hour,car[i].setout.minutes);
			printf("%s\t%s\t%.1f\t%d\t%d\t",car[i].beginpoint,car[i].endpoint,car[i].lasttime,car[i].fixnumber,car[i].fixednumber);
			printf("(此车已出发)\n");
		}
	}
}
void SearchMessage()
{
	int functionnumber;
	printf("查询子菜单:\n");
	printf("=========================================================================\n");
	printf(" 1.按班次号查询\n");
	printf(" 2.按终点站查询\n");
	printf(" 3.返回主菜单\n");
	printf("=========================================================================\n");
	printf("请选择你需要的功能:");
	scanf("%d",&functionnumber);
	switch(functionnumber)
	{	
		case (1):system("cls");searchbynumber();break;
		case (2):system("cls");searchbyaddress();break;
		case (3):system("cls");mainmenu();break;
		default:printf("输入错误，请确保你的输入为1-3.\n");
		printf("请按任意键返回查询子菜单\n");
		getchar();
		getchar();
		SearchMessage();
	}
}
void searchbynumber()
{
	int searchnumber;
	int slogan=1,i;
	printf("请输入你要查询的班次号:");
	scanf("%d",&searchnumber);
	for(i=0;i<count;i++)
	{
		if(searchnumber==car[i].carnumber)
		{
			printf("班次 发车时间 起点 终点 行车时间(小时) 额定载量 已订票人数\n");
			if(car[i].setout.minutes>=0&&car[i].setout.minutes<=9)
				printf("%d\t%d:0%d\t",car[i].carnumber,car[i].setout.hour,car[i].setout.minutes);
			else
				printf("%d\t%d:%d\t",car[i].carnumber,car[i].setout.hour,car[i].setout.minutes);
			printf("%s\t%s\t%.1f\t%d\t%d\t\n",car[i].beginpoint,car[i].endpoint,car[i].lasttime,car[i].fixnumber,car[i].fixednumber);
			slogan=0;	break; 
		}
	}
	if(slogan) 
		printf("对不起，没有这趟车.");
}
void searchbyaddress()
{
	int i,flag=1;
	char address[20];
	printf("请输入终点站名:");
	scanf("%s",address);
	for(i=0;i<count;i++)
		if(strcmp(address,car[i].endpoint)==0)
		{
			printf("班次 发车时间 起点 终点 行车时间(小时) 额定载量 已订票人数\n");
			printf("%d\t%d:%d\t",car[i].carnumber,car[i].setout.hour,car[i].setout.minutes);
			printf("%s\t%s\t%.1f\t%d\t%d\t\n",car[i].beginpoint,car[i].endpoint,car[i].lasttime,car[i].fixnumber,car[i].fixednumber);	flag=0;
		}
	if(flag)
		printf("对不起，没有这趟车.");
}
void TicketManagement()
{
	char functionnumber;
	printf("==========================================================================\n");
	printf(" 1.订票.\n");
	printf(" 2.退票.\n");
	printf(" 3.返回主菜单.\n");
	printf("==========================================================================\n");
	printf("请选择你需要的功能:\n");
	scanf("%s",&functionnumber);
	switch(functionnumber)
	{
		case '1':system("cls");
		TicketOrder();break;
		case '2':system("cls");
		TicketDelete();
		break;
		case '3':system("cls");
		{mainmenu();}break;
		default:
		{
			printf("输入错误，请确保你的输入为1--3.\n");
			printf("按任意键返回子菜单.\n");
			getchar();getchar();
			TicketManagement();
		}
	}
}
void TicketOrder()
{
	int i,slogan=1;
	int s;
	printf("请输入要订购的车票的班次：\n");
	scanf("%d",&i);
	for(s=0;s<count;s++)
		if(i==car[s].carnumber)
		{
			slogan=0;
			break;
		}
	if(slogan)
	{
		printf("对不起，没有这趟车，请查询后再订票.\n");
		printf("按任意键返回车票管理菜单。");
		getchar();
		getchar();
		TicketManagement();
	}
	else
	{
		time_t tval;
		struct tm*now;
		tval=time(NULL);
		now=localtime(&tval);
		if((now->tm_hour==car[s].setout.hour&&now->tm_min<car[s].setout.minutes)||(now->tm_hour<car[s].setout.hour))
		{
			if(car[s].fixednumber<car[s].fixnumber)
			{
				car[s].fixednumber++;
				RefreshData();
				printf("你的订票成功，请按时上车，谢谢使用！\n");
			}
			else 
			printf("对不起，今天的这趟车的票已卖完，请明天再来，谢谢合作！\n");
		}
		else
		printf("对不起，今天的这趟车已出发，请明天再来，谢谢合作！\n");
	}
	printf("班次 发车时间 起点 终点 行车时间(小时) 额定载量 已订票人数\n");
	if(car[s].setout.minutes>=0&&car[s].setout.minutes<=9)
		printf("%d\t%d:0%d\t",car[s].carnumber,car[s].setout.hour,car[s].setout.minutes);
	else
		printf("%d\t%d:%d\t",car[s].carnumber,car[s].setout.hour,car[s].setout.minutes);
	printf("%s\t%s\t%.1f\t%d\t%d\t",car[s].beginpoint,car[s].endpoint,car[s].lasttime,car[s].fixnumber,car[s].fixednumber);
	printf("按任意键返回主菜单。\n");
	getchar();
	getchar();
}
void TicketDelete()
{
	int i,slogan=1;
	int s;
	printf("请输入要退购的车票的班次：\n");
	scanf("%d",&i);
	for(s=0;s<count;s++)
		if(i==car[s].carnumber)
		{
			slogan=0;
			break;
		}
	if(slogan)
	{
		printf("对不起，没有这趟车，请查询后再退票.\n");
		printf("按任意键返回车票管理菜单。");
		getchar();
		getchar();
		TicketManagement();
	}
	else
	{
		time_t tval;
		struct tm*now;
		tval=time(NULL);
		now=localtime(&tval);
		if((now->tm_hour==car[s].setout.hour&&now->tm_min<car[s].setout.minutes)||(now->tm_hour<car[s].setout.hour))
		{
			if(car[s].fixednumber<car[s].fixnumber)
			{
				car[s].fixednumber--;
				RefreshData();
				printf("退票成功，谢谢使用！\n");
			}
			else
				printf("对不起，今天的这趟车的票尚未卖出，无法完成退票！\n");
		}
		else
		printf("对不起，今天的这趟车已出发，无法完成退票！\n");
	}
	printf("班次 发车时间 起点 终点 行车时间(小时) 额定载量 已订票人数\n");
	if(car[s].setout.minutes>=0&&car[s].setout.minutes<=9)
		printf("%d\t%d:0%d\t",car[s].carnumber,car[s].setout.hour,car[s].setout.minutes);
	else
		printf("%d\t%d:%d\t",car[s].carnumber,car[s].setout.hour,car[s].setout.minutes);
	printf("%s\t%s\t%.1f\t%d\t%d\t",car[s].beginpoint,car[s].endpoint,car[s].lasttime,car[s].fixnumber,car[s].fixednumber);
	printf("按任意键返回主菜单。\n");
	getchar();
	getchar();
}

void RefreshData()
{
	FILE *fp;
	if((fp=fopen("班次信息.txt","w+"))==NULL)
	{
		printf("error!");
		exit(0);
	}
	rewind(fp);
	int i;
	for(i=0;i<count;i++)
	{
		fprintf(fp,"%d\t",car[i].carnumber);
		if(car[i].setout.minutes>=0&&car[i].setout.minutes<=9)
			fprintf(fp,"%d:0%d\t",car[i].setout.hour,car[i].setout.minutes);
		else
			fprintf(fp,"%d:%d\t",car[i].setout.hour,car[i].setout.minutes);
		fprintf(fp,"%s\t",car[i].beginpoint);
		fprintf(fp,"%s\t",car[i].endpoint);
		fprintf(fp,"%.1f\t",car[i].lasttime);
		fprintf(fp,"%d\t",car[i].fixnumber);
		fprintf(fp,"%d\n",car[i].fixednumber); 
	}
}