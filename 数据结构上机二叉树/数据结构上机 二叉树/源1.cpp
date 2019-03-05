#include<iostream>
#include<cstring>
#include<iomanip>
#include<string.h>
#include<ctype.h>
#include<malloc.h> /* malloc()等 */
#include<limits.h> /* INT_MAX等 */
#include<stdio.h> /* EOF(=^Z或F6),NULL */
#include<stdlib.h> /* atoi() */
#include<io.h> /* eof() */
#include<cmath> /* floor(),ceil(),abs() */
#include<process.h> 
using namespace std;
const char Nil = ' ';

//定义树
struct BiTNode
{
	char data;
	BiTNode*lchild, *rchild;
};
typedef BiTNode *BiTree;


//定义队列
typedef struct QNode
{
	BiTree data;
	QNode*next;
}QNode, *QueuePtr;
typedef struct LinkQueue
{
	QueuePtr font, rear;
}LinkQueue,*LinkQu;
//定义栈
const int InitSize = 10;
const int AddSize = 2;
typedef struct SqStack
{
	BiTree*base;
	BiTree*top;
	int stacksize;
}SqStack,*SqSt;




//队列的 基本操作
void IniQueue(LinkQu T)
{
	T->font = T->rear = (QueuePtr)malloc(sizeof(QNode));
	T->font->next = NULL;
}
void DestroyQueue(LinkQu T)
{
	while (T->font)
	{
		T->rear = T->font->next;
		free(T->font);
		T->font = T->rear;
}
}
void ClearQueue(LinkQu T)
{
	QueuePtr p,q;
	T->rear = T->font;
	p = T->font->next;
	T->font->next = NULL;
	while (p)
	{
		q = p;
		p = p->next;
		free(p);
	}
}
int QueueEmpty(LinkQueue  T)
{
	if (T.font = T.rear)
		return true;
	else return false;
}
int QueueLength(LinkQueue T)
{
	int i = 0;
	QueuePtr p;
	p = T.font;
	while (p != T.rear)
	{
		i++;
		p = p->next;
	}
	return i;
}
void GetHead_Q(LinkQueue T, BiTree*e)
{
	QueuePtr p;
	p = T.font->next;
	*e = p->data;
}
void EnQueue(LinkQu T, BiTree e)
{
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	p->data = e;
	p->next=NULL;
	T->rear->next = p;
	T->rear = p;
}
void DeQueue(LinkQu T, BiTree*e)
{
	QueuePtr p = T->font->next;
	*e = p->data;
	T->font->next =p->next;
	if (T->rear = p)
		T->rear = T->font;
	free(p);
}
void QueueTraverse(LinkQueue T, void(*visit)(BiTree))
{
	QueuePtr p;
	p = T.font->next;
	while (p)
	{
		visit(p->data);
		p = p->next;
	}
	cout << endl;
}



//栈 的基本操作
void InitStack(SqSt S)
{
	S->base = (BiTree*)malloc(InitSize * sizeof(BiTree));
	S->top = S->base;
	S->stacksize = InitSize;
}
void DestroyStack(SqSt S)
{
	free(S->base);
	S->base = NULL;
	S->top = NULL;
	S->stacksize = 0;
}
void ClearStack(SqSt S)
{
	S->top = S->base;
}
int StackEmpty(SqSt S)
{
	if (S->top == S->base)
		return true;
	else return false;
}
int StackLength(SqSt S)
{
	return S->top - S->base;
}
int GetTop(SqSt S,BiTree*e)
{
	if (S->top > S->base)
	{
		*e = *(S->top - 1);
		return 1;
	}
	else return 0;
}
void Push(SqSt S, BiTree e)
{
	if (S->top - S->base >= S->stacksize)
	{
		S->base = (BiTree*)realloc(S->base,(S->stacksize + AddSize) * sizeof(BiTree));
		S->top = S->base + S->stacksize;
	}
	*S->top++ = e;
}
void Pop(SqSt S, BiTree*e)
{
	*e = *(--S->top);
}
void StackTraverse(SqSt S, void(*visit)(BiTree))
{
	while (S->top > S->base)
		visit(*(S->base)++);
	cout << endl;
}
void visitT(char e)
{
	cout << e;
}



//树的基本操作
int InitBiTree(BiTree *T)
{
	*T = NULL;
	return 0;
}
void DestroyBiTree(BiTree *T)
{
	if (*T) 
	{
		if ((*T)->lchild)
			DestroyBiTree(&(*T)->lchild); 
		if ((*T)->rchild) 
			DestroyBiTree(&(*T)->rchild); 
		free(*T); 
		*T = NULL; 
	}
}
void CreateBiTree(BiTree *T)
{ 
	char ch;
	cin >> ch;
	if (ch == Nil) /* 空 */
		*T = NULL;
	else
	{
		*T = (BiTree)malloc(sizeof(BiTNode));
		/*if (!*T)
			exit(OVERFLOW);*/
		(*T)->data = ch; 
		CreateBiTree(&(*T)->lchild); 
		CreateBiTree(&(*T)->rchild); 
	}
}

int BiTreeEmpty(BiTree T)
{ 
	if (T)
		return -1;
	else
		return 0;
}

#define ClearBiTree DestroyBiTree

int BiTreeDepth(BiTree T)
{ 
	int i, j;
	if (!T)
		return 0;
	if (T->lchild)
		i = BiTreeDepth(T->lchild);
	else
		i = 0;
	if (T->rchild)
		j = BiTreeDepth(T->rchild);
	else
		j = 0;
	return i>j ? i + 1 : j + 1;
}

char Root(BiTree T)
{ 
	if (BiTreeEmpty(T))
		return Nil;
	else
		return T->data;
}

char Value(BiTree p)
{
	return p->data;
}

void Assign(BiTree p, char e)
{ 
	p->data = e;
}

//利用队列进行操作
char Parent(BiTree T, char e)
{
	LinkQueue q;
	BiTree a;
	if (T)
	{
		IniQueue(&q);
		EnQueue(&q, T);
		while (!QueueEmpty(q))
		{
			DeQueue(&q, &a);
			if (a->lchild&&a->lchild->data == e || a->rchild&&a->rchild->data == e)
				return a->data;
			else
			{
				if (a->lchild)
					EnQueue(&q, a->lchild);
				if (a->rchild)
					EnQueue(&q, a->rchild);
			}
		}
	}
	return Nil;
}
BiTree Point(BiTree T, char s)
{ /* 返回二叉树T中指向元素值为s的结点的指针。另加 */
	LinkQueue q;
	BiTree a;
	if (T) /* 非空树 */
	{
		IniQueue(&q); /* 初始化队列 */
		EnQueue(&q, T); /* 根结点入队 */
		while (!QueueEmpty(q)) /* 队不空 */
		{
			DeQueue(&q, &a); /* 出队,队列元素赋给a */
			if (a->data == s)
				return a;
			if (a->lchild) /* 有左孩子 */
				EnQueue(&q, a->lchild); /* 入队左孩子 */
			if (a->rchild) /* 有右孩子 */
				EnQueue(&q, a->rchild); /* 入队右孩子 */
		}
	}
	return NULL;
}

char LeftChild(BiTree T, char e)
{ /* 初始条件: 二叉树T存在,e是T中某个结点 */
  /* 操作结果: 返回e的左孩子。若e无左孩子,则返回＂空＂ */
	BiTree a;
	if (T) /* 非空树 */
	{
		a = Point(T, e); /* a是结点e的指针 */
		if (a&&a->lchild) /* T中存在结点e且e存在左孩子 */
			return a->lchild->data; /* 返回e的左孩子的值 */
	}
	return Nil; /* 其余情况返回空 */
}

char RightChild(BiTree T,char e)
{ /* 初始条件: 二叉树T存在,e是T中某个结点 */
  /* 操作结果: 返回e的右孩子。若e无右孩子,则返回＂空＂ */
	BiTree a;
	if (T) /* 非空树 */
	{
		a = Point(T, e); /* a是结点e的指针 */
		if (a&&a->rchild) /* T中存在结点e且e存在右孩子 */
			return a->rchild->data; /* 返回e的右孩子的值 */
	}
	return Nil; /* 其余情况返回空 */
}

char LeftSibling(BiTree T, char e)
{ /* 初始条件: 二叉树T存在,e是T中某个结点 */
  /* 操作结果: 返回e的左兄弟。若e是T的左孩子或无左兄弟,则返回＂空＂ */
	char a;
	BiTree p;
	if (T) /* 非空树 */
	{
		a = Parent(T, e); /* a为e的双亲 */
		p = Point(T, a); /* p为指向结点a的指针 */
		if (p->lchild&&p->rchild&&p->rchild->data == e) /* p存在左右孩子且右孩子是e */
			return p->lchild->data; /* 返回p的左孩子(e的左兄弟) */
	}
	return Nil; /* 树空或没找到e的左兄弟 */
}

char RightSibling(BiTree T, char e)
{ /* 初始条件: 二叉树T存在,e是T中某个结点 */
  /* 操作结果: 返回e的右兄弟。若e是T的右孩子或无右兄弟,则返回＂空＂ */
	char a;
	BiTree p;
	if (T) /* 非空树 */
	{
		a = Parent(T, e); /* a为e的双亲 */
		p = Point(T, a); /* p为指向结点a的指针 */
		if (p->lchild&&p->rchild&&p->lchild->data == e) /* p存在左右孩子且左孩子是e */
			return p->rchild->data; /* 返回p的右孩子(e的右兄弟) */
	}
	return Nil; /* 树空或没找到e的右兄弟 */
}

void InsertChild(BiTree p, int LR, BiTree c) /* 形参T无用 */
{ /* 初始条件: 二叉树T存在, p指向T中某个结点, LR为0或1, */
  /*           非空二叉树c与T不相交且右子树为空 */
  /* 操作结果: 根据LR为0或1,插入c为T中p所指结点的左或右子树。p所指结点的 */
  /*           原有左或右子树则成为c的右子树 */
	if (p) /* p不空 */
	{
		if (LR == 0)
		{
			p->lchild = c;
		}
		else /* LR==1 */
		{
			p->rchild = c;
		}
		
	}
	
}

void DeleteChild(BiTree p, int LR) /* 形参T无用 */
{ /* 初始条件: 二叉树T存在,p指向T中某个结点,LR为0或1 */
  /* 操作结果: 根据LR为0或1,删除T中p所指结点的左或右子树 */
	if (p) /* p不空 */
	{
		if (LR == 0) /* 删除左子树 */
			ClearBiTree(&p->lchild);
		else /* 删除右子树 */
			ClearBiTree(&p->rchild);
		
	}
	
}

void PreOrderTraverse(BiTree T, void(*Visit)(char))
{ /* 初始条件: 二叉树T存在,Visit是对结点操作的应用函数。算法6.1，有改动 */
  /* 操作结果: 先序递归遍历T,对每个结点调用函数Visit一次且仅一次 */
	if (T) /* T不空 */
	{
		Visit(T->data); /* 先访问根结点 */
		PreOrderTraverse(T->lchild, Visit); /* 再先序遍历左子树 */
		PreOrderTraverse(T->rchild, Visit); /* 最后先序遍历右子树 */
	}
}

void InOrderTraverse(BiTree T, void(*Visit)(char))
{ /* 初始条件: 二叉树T存在,Visit是对结点操作的应用函数 */
  /* 操作结果: 中序递归遍历T,对每个结点调用函数Visit一次且仅一次 */
	if (T)
	{
		InOrderTraverse(T->lchild, Visit); /* 先中序遍历左子树 */
		Visit(T->data); /* 再访问根结点 */
		InOrderTraverse(T->rchild, Visit); /* 最后中序遍历右子树 */
	}
}





//
void InOrderTraverse1(BiTree T, void(*Visit)(char))
{ /* 采用二叉链表存储结构，Visit是对数据元素操作的应用函数。算法6.3 */
  /* 中序遍历二叉树T的非递归算法(利用栈)，对每个数据元素调用函数Visit */
	SqStack S;
	InitStack(&S);
	while (T || !StackEmpty(&S))
	{
		if (T)
		{ /* 根指针进栈,遍历左子树 */
			Push(&S, T);
			T = T->lchild;
		}
		else
		{ /* 根指针退栈,访问根结点,遍历右子树 */
			Pop(&S, &T);
			
			T = T->rchild;
		}
	}
	cout << endl;
	
}

void InOrderTraverse2(BiTree T, void(*Visit)(char))
{ /* 采用二叉链表存储结构，Visit是对数据元素操作的应用函数。算法6.2 */
  /* 中序遍历二叉树T的非递归算法(利用栈)，对每个数据元素调用函数Visit */
	SqStack S;
	BiTree p;
	InitStack(&S);
	Push(&S, T); /* 根指针进栈 */
	while (!StackEmpty(&S))
	{
		while (GetTop(&S, &p) && p)
			Push(&S, p->lchild); /* 向左走到尽头 */
		Pop(&S, &p); /* 空指针退栈 */
		if (!StackEmpty(&S))
		{ /* 访问结点,向右一步 */
			Pop(&S, &p);
			
			Push(&S, p->rchild);
		}
	}
	cout << endl;
	
}

void PostOrderTraverse(BiTree T, void(*Visit)(char))
{ /* 初始条件: 二叉树T存在,Visit是对结点操作的应用函数 */
  /* 操作结果: 后序递归遍历T,对每个结点调用函数Visit一次且仅一次 */
	if (T) /* T不空 */
	{
		PostOrderTraverse(T->lchild, Visit); /* 先后序遍历左子树 */
		PostOrderTraverse(T->rchild, Visit); /* 再后序遍历右子树 */
		Visit(T->data); /* 最后访问根结点 */
	}
}

void LevelOrderTraverse(BiTree T, void(*Visit)(char))
{ /* 初始条件：二叉树T存在,Visit是对结点操作的应用函数 */
  /* 操作结果：层序递归遍历T(利用队列),对每个结点调用函数Visit一次且仅一次 */
	LinkQueue q;
	BiTree a;
	if (T)
	{
		IniQueue(&q);
		EnQueue(&q, T);
		while (!QueueEmpty(q))
		{
			DeQueue(&q, &a);
			Visit(a->data);
			if (a->lchild != NULL)
				EnQueue(&q, a->lchild);
			if (a->rchild != NULL)
				EnQueue(&q, a->rchild);
		}
		cout << endl;
	}
}

int main()
{
	
	BiTree T, T2, T3;
	char e1, e2;
	InitBiTree(&T);
	cout<<"请先序输入二叉树(如:ab三个空格表示a为根结点,b为左子树的二叉树)\n";
	CreateBiTree(&T);
	cout << "2";
	e1 = Root(T);
	cout << "1";
	if (e1 != Nil)

		cout << "二叉树的根为: \n" << e1;
	else
		cout << "树空，无根\n" << endl;
	int a, b, c;
	cout << "请选择您想要完成的操作：1.中序递归遍历二叉树  2.中序非递归遍历二叉树1 3.中序非递归遍历二叉树2" << endl;
	cout << "                         4.后续递归遍历二叉树 5.层序递归遍历二叉树\n";
	cin >> a;
	switch (a)
	{
	case 1:
		printf("中序递归遍历二叉树:\n");
		InOrderTraverse(T, visitT);
		break;
	case 2:
		printf("\n中序非递归遍历二叉树:\n");
		InOrderTraverse1(T, visitT);
		break;
	case 3:
		printf("中序非递归遍历二叉树(另一种方法):\n");
		InOrderTraverse2(T, visitT);
		break;
	case 4:
		printf("后序递归遍历二叉树:\n");
		PostOrderTraverse(T, visitT);
		break;
	case 5:
		printf("\n层序遍历二叉树:\n");
		LevelOrderTraverse(T, visitT);
		break;
	}

	printf("请输入一个结点的值: ");
	cin >> e1;
	T2 = Point(T, e1);
	printf("欲改变此结点的值，请输入新值: ");
	cin >> e2;

	Assign(T2, e2);
	printf("层序遍历二叉树:\n");
	LevelOrderTraverse(T, visitT);
	e1 = Parent(T, e2);
	if (e1 != Nil)

		printf("%c的双亲是%c\n", e2, e1);
	else
		printf("%c没有双亲\n", e2);
	e1 = LeftChild(T, e2);
	if (e1 != Nil)

		printf("%c的左孩子是%c\n", e2, e1);

	else
		printf("%c没有左孩子\n", e2);
	e1 = RightChild(T, e2);
	if (e1 != Nil)
		printf("%c的右孩子是%c\n", e2, e1);
	else
		printf("%c没有右孩子\n", e2);
	e1 = LeftSibling(T, e2);
	if (e1 != Nil)
		printf("%c的左兄弟是%c\n", e2, e1);

	else
		printf("%c没有左兄弟\n", e2);
	e1 = RightSibling(T, e2);
	if (e1 != Nil)
		printf("%c的右兄弟是%c\n", e2, e1);
	else
		printf("%c没有右兄弟\n", e2);
	system("pause");


}