#include<stdio.h>
#include<stdlib.h>

#define ok 1
#define error 0
#define overflow -1
#define maxstrlen 255

typedef unsigned char sstring[maxstrlen + 1];//s[0]用来存放长度
typedef int status; 
typedef char elemtype;

status strassign(sstring &s)//生成字符串
{
	int i = 1;
	char ch;
	printf("\n请输入字符串：");
	scanf("%c", &ch);
	while (ch != '\n')
	{
		s[i] = ch;
		i++;
		scanf("%c", &ch);
	}
	s[i+1]='\0';
	s[0] = i - 1;
	return ok;
}

status strcopy(sstring &t, sstring s)//有串S复制得串T
{
	if (!s)
		return error;//s是空串则无法复制
	for(int i=0;i<=s[0];i++)
		t[i]=s[i];
	return ok;

}

status strprint(sstring s)//遍历字符串
{
	
	if (!s)
		return error;
	for(int i=1;i<=s[0];i++)
		printf("%c",s[i]);
		return ok;

}

status listempty(sstring s)//判断s是否为空串
{
	if (s[0] == 0)
		return ok;
	else
		return error;
}

void strlength(sstring s)//输出字符串的长度
{
	printf("\n此字符串的长度为:%d\n", s[0]);
}

int strcompare(sstring s, sstring t)//s与t比较大小
{
	if (!t || !s)
		return error;

	for(int i=0;i<s[0];i++)
	{
		if(s[i]>t[i])
			return 1;
		else if(s[i]<t[i])
			return -1;
	}
	return 0;

}

status concat(sstring &t, sstring s1, sstring s2)//将串s1和s2连接起来，用t返回
{
	int i;
	if (s1[0] + s2[0] <= maxstrlen + 1)//未截断
	{
		for (i = 1; i <= s1[0]; i++)
			t[i] = s1[i];
		for (i = 1; i <= s2[0]; i++)
			t[i+s1[0]] = s2[i];//此时串s1已经复制好了，所以t从s[0]+1开始
		t[0] = s1[0] + s2[0];//t的长度为s1+s2
		return ok;
	}
	else if (s1[0]<maxstrlen)
	{
		for (i = 1; i <= s1[0]; i++)
			t[i] = s1[i];
		for (i = 1; i <= maxstrlen - s1[0]; i++)
			t[s1[0] + i] = s2[i];
		t[0] = maxstrlen;
		return error;
	}
	else
	{
		for (i = 1; i <= maxstrlen; i++)
			t[i] = s1[i];
		t[0] = maxstrlen;
		return error;
	}
}

status subtring(sstring &sub,sstring s,int pos,int len)//用sub返回串s 的第pos个长度为len的字串
{
	if (pos<1 || pos>s[0] || len<0 || len>s[0] - pos + 1)
		return error;
		
	sub[0]=len;
	for(int i=pos;i<=len+pos;i++)
		sub[i+1-pos]=s[i];
	return ok;

}

int index(sstring s, sstring t, int pos)//求串t在s中第一次出现的位置
{
	if (!t || pos<1 || pos>s[0])
		return error;
		
int i = pos;//i-主串S中当前位置下标，若pos不为1，从pos位置开始匹配
	int j = 1;// //j用于子串T中当前位置的下标值
	while (i <= s[0] && j <= t[0])//如果j>t[0]说明匹配成功，跳出循环
	{
		if (s[i] == t[j])//两字母相同时，继续循环，向后移动
		{
			i++;
			j++;
		}
		else//俩字母不同时，i退回到上次匹配首位的下一位，j重置为1
		{
			i = i - j + 2;
			j = 1;
		}
	}
		if (j >t[0])
			return i - t[0];//或者是返回i-j+1也可以
		else 
			return error;//i>s[0],则匹配失败

}

status clearstr(sstring &s)//置空串
{
	s[0] = 0;
	return ok;
}

status strinser(sstring &s, int pos, sstring t)//在串s的第pos个字符之后插入串t
{
	if (!s || !t || pos<1 || pos>s[0] + 1)
		return error;
	int i,j;

	
	if (s[0] + t[0] <= maxstrlen)
	{
		s[0] += t[0];
		for (i = s[0]; i >= pos; i--)
			s[i+t[0] ] = s[i];//pos的后半部分往后移
		for (i = pos; i<pos+t[0]; i++)
			s[i] = t[i-pos+1];//在pos的位置开始插入t，j控制t的小标
		return ok;
	}
	
	
	else
	{
		for (i = maxstrlen; i >= pos + t[0]; i--)
			s[i] = s[i - t[0]];
		for (i = pos; i<(pos + t[0]) && i <= maxstrlen; i++)
			s[i] = t[i - pos + 1];
		s[0] = maxstrlen;
		return ok;
	}
}


status strdelete(sstring &s, int pos, int len)//从串s中删除第pos个字符起长度为len的字串
{
	if (!s || pos<1 || pos>s[0] - len + 1)
		return error;
	
	for(int i=pos;i<s[0]-len;i++)
		s[i]=s[i+len];
	s[0]=s[0]-len;
	return ok;

}

status destorystring(sstring &s)//串s被销毁
{
	free(s);
	return ok;
}

int main()
{
	sstring s,t,s1,s2,sub;
	int i=3,m;
	int pos = 2;
	printf("输入字符串s：");
	strassign(s);
	printf("s:");
	strprint(s); // 待完成
	strlength(s);
	strcopy(t, s); // 待完成
	printf("将串s复制到串t\n");
	printf("t:");
	strprint(t);
	printf("\n输入新的字符串t：");
	strassign(t);
	printf("t:\n");
	strprint(t);
	m = strcompare(s, t); // 待完成
	if (m > 0)
		printf("串s大于串t\n");
	else if (m == 0)
		printf("串s和串t相等\n");
	else
		printf("串s小于串t\n");
	printf("将串s和串t链接后的字符串 s1：\n");
	concat(s1, s, t);
	strprint(s1);
	printf("\n当pos=5，len=4时s的字串为:\n");
	subtring(sub, s, 5, 4); // 待完成
	strprint(sub);
	printf("\n");
	i = index(s, t,pos);
	if (i == 0)
		printf("串t在串s中不存在\n");
	else
		printf("t在从%d个字符之后在s中出现的的第一个位置是%d\n" ,pos,i);
	printf("在s的第五个位置插入字符串t后,s:\n");
	strinser(s, 5, t);
	strprint(s);
	printf("\n在s的第五个位置起删除长度为4的字符串后,s:");
	strdelete(s, 5, 4); // 待完成
	strprint(s);
	printf("\n");
	system("pause");
	return 0;
}
