#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace std;
FILE *fp;
const int IniSize = 2;
struct SqStack//类型定义
{
	int *base;
	int*top;
	int     stacksize;
};

void InitStack(SqStack *S)//初始化栈
{
	(*S).base = (int *)malloc(IniSize * sizeof(int));
	if (!(*S).base)
		exit(OVERFLOW);
	(*S).stacksize = IniSize;
	(*S).top = (*S).base;
}

void ClearStack(SqStack *S)//清空栈
{
	(*S).top = (*S).base;
}
void DestroyStack(SqStack *S)//销毁栈
{
	free((*S).base);
	(*S).stacksize = 0;
	(*S).base = NULL;
	(*S).top = NULL;
}


void Push(SqStack *S, char e)//进栈
{
	int&a = (*S).stacksize;
	if ((*S).top - (*S).base >= a)
	{
		(*S).base = (int *)realloc((*S).base, ((*S).stacksize + IniSize) * sizeof(int));
		if (!(*S).base)
			exit(0);
		(*S).top = (*S).base + a;
		a += IniSize;
	}
	*(*S).top++ = e;
}

int Pop(SqStack *S, char &e)//出栈
{
	if ((*S).top != (*S).base)
		e = *--(*S).top;
	return 0;
}
void Copy(int c)//将单个元素放入文档
{
	fputc(c, fp);
}
void Traverse(SqStack S)//遍历所有元素并将它们放入文档
{
	while (S.top>S.base)
		Copy(*S.base++);
}
int main()
{
	fp = fopen("UserSavingStack.txt", "w");
	SqStack S;
	char ch, c;
	InitStack(&S);
	cout << "请输入您想输入的数据测试栈, 输入#表示出栈顶元素，@表示清空栈，Enter换行表示清空栈并换行建立新栈\n按Ctrl+Z键结束文本输入" << endl;
	ch = getchar();
	while (ch != EOF)
	{
		while (ch != '\n')
		{
			switch (ch)
			{
			case '#':   Pop(&S, c);    break;
			case '@':  ClearStack(&S);   break;
			default:   Push(&S, ch);
			}
			ch = getchar();
		}
		Traverse(S);
		ClearStack(&S);
		fputc('\n', fp);
		if (ch != EOF)
			ch = getchar();
	}
	DestroyStack(&S);
	fclose(fp);
	system("pause");
}