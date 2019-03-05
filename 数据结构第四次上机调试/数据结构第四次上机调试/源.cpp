#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace std;
FILE *fp;
const int IniSize = 2;
struct SqStack//���Ͷ���
{
	int *base;
	int*top;
	int     stacksize;
};

void InitStack(SqStack *S)//��ʼ��ջ
{
	(*S).base = (int *)malloc(IniSize * sizeof(int));
	if (!(*S).base)
		exit(OVERFLOW);
	(*S).stacksize = IniSize;
	(*S).top = (*S).base;
}

void ClearStack(SqStack *S)//���ջ
{
	(*S).top = (*S).base;
}
void DestroyStack(SqStack *S)//����ջ
{
	free((*S).base);
	(*S).stacksize = 0;
	(*S).base = NULL;
	(*S).top = NULL;
}


void Push(SqStack *S, char e)//��ջ
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

int Pop(SqStack *S, char &e)//��ջ
{
	if ((*S).top != (*S).base)
		e = *--(*S).top;
	return 0;
}
void Copy(int c)//������Ԫ�ط����ĵ�
{
	fputc(c, fp);
}
void Traverse(SqStack S)//��������Ԫ�ز������Ƿ����ĵ�
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
	cout << "������������������ݲ���ջ, ����#��ʾ��ջ��Ԫ�أ�@��ʾ���ջ��Enter���б�ʾ���ջ�����н�����ջ\n��Ctrl+Z�������ı�����" << endl;
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