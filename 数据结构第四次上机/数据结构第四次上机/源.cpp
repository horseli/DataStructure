#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define STACK_INIT_SIZE 10
#define STACKINCREMENT   2
#define    OK      1
#define    FALSE 0

typedef int SElemType;
typedef int Status;

FILE *fp;

typedef struct SqStack
{
	SElemType *base;
	SElemType *top;
	int     stacksize;
}SqStack;

Status InitStack(SqStack *S)
{
	(*S).base = (SElemType *)malloc(STACK_INIT_SIZE * sizeof(SElemType));
	if (!(*S).base)
		exit(OVERFLOW);
	(*S).top = (*S).base;
	(*S).stacksize = STACK_INIT_SIZE;
	return OK;
}

Status DestroyStack(SqStack *S)
{
	free((*S).base);
	(*S).base = NULL;
	(*S).top = NULL;
	(*S).stacksize = 0;
	return OK;
}

Status ClearStack(SqStack *S)
{
	(*S).top = (*S).base;
	return OK;
}

Status Push(SqStack *S, SElemType e)
{
	if ((*S).top - (*S).base >= (*S).stacksize)
	{
		(*S).base = (SElemType *)realloc((*S).base, ((*S).stacksize + STACKINCREMENT) * sizeof(SElemType));
		if (!(*S).base)
			exit(OVERFLOW);
		(*S).top = (*S).base + (*S).stacksize;
		(*S).stacksize += STACKINCREMENT;
	}
	*((*S).top)++ = e;
	return OK;
}

Status Pop(SqStack *S, SElemType *e)
{
	if ((*S).top == (*S).base)
		return FALSE;
	*e = *--(*S).top;
	return OK;
}


Status StackTraverse(SqStack S, Status(*visit)(SElemType))
{
	while (S.top>S.base)
		visit(*S.base++);
	printf("\n");
	return OK;
}

Status Copy(SElemType c)
{
	fputc(c, fp);
	return OK;
}

void LineEdit()
{
	SqStack S;
	SElemType ch, c;
	InitStack(&S);
	printf("请输入文本, 按Ctrl+Z键结束文本输入:\n");
	ch = getchar();
	while (ch != EOF)
	{
		while (ch != EOF&&ch != '\n')
		{
			switch (ch)
			{
			case '#':   Pop(&S, &c);    break;
			case '@':  ClearStack(&S);   break;
			default:   Push(&S, ch);
			}
			ch = getchar();
		}
		StackTraverse(S, Copy);
		ClearStack(&S);
		fputc('\n', fp);
		if (ch != EOF)
			ch = getchar();
	}
	DestroyStack(&S);
}

void main()
{
	fp = fopen("LineEd.txt", "w");
	LineEdit();
	fclose(fp);
}