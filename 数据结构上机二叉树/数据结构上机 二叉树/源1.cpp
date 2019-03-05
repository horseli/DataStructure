#include<iostream>
#include<cstring>
#include<iomanip>
#include<string.h>
#include<ctype.h>
#include<malloc.h> /* malloc()�� */
#include<limits.h> /* INT_MAX�� */
#include<stdio.h> /* EOF(=^Z��F6),NULL */
#include<stdlib.h> /* atoi() */
#include<io.h> /* eof() */
#include<cmath> /* floor(),ceil(),abs() */
#include<process.h> 
using namespace std;
const char Nil = ' ';

//������
struct BiTNode
{
	char data;
	BiTNode*lchild, *rchild;
};
typedef BiTNode *BiTree;


//�������
typedef struct QNode
{
	BiTree data;
	QNode*next;
}QNode, *QueuePtr;
typedef struct LinkQueue
{
	QueuePtr font, rear;
}LinkQueue,*LinkQu;
//����ջ
const int InitSize = 10;
const int AddSize = 2;
typedef struct SqStack
{
	BiTree*base;
	BiTree*top;
	int stacksize;
}SqStack,*SqSt;




//���е� ��������
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



//ջ �Ļ�������
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



//���Ļ�������
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
	if (ch == Nil) /* �� */
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

//���ö��н��в���
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
{ /* ���ض�����T��ָ��Ԫ��ֵΪs�Ľ���ָ�롣��� */
	LinkQueue q;
	BiTree a;
	if (T) /* �ǿ��� */
	{
		IniQueue(&q); /* ��ʼ������ */
		EnQueue(&q, T); /* �������� */
		while (!QueueEmpty(q)) /* �Ӳ��� */
		{
			DeQueue(&q, &a); /* ����,����Ԫ�ظ���a */
			if (a->data == s)
				return a;
			if (a->lchild) /* ������ */
				EnQueue(&q, a->lchild); /* ������� */
			if (a->rchild) /* ���Һ��� */
				EnQueue(&q, a->rchild); /* ����Һ��� */
		}
	}
	return NULL;
}

char LeftChild(BiTree T, char e)
{ /* ��ʼ����: ������T����,e��T��ĳ����� */
  /* �������: ����e�����ӡ���e������,�򷵻أ��գ� */
	BiTree a;
	if (T) /* �ǿ��� */
	{
		a = Point(T, e); /* a�ǽ��e��ָ�� */
		if (a&&a->lchild) /* T�д��ڽ��e��e�������� */
			return a->lchild->data; /* ����e�����ӵ�ֵ */
	}
	return Nil; /* ����������ؿ� */
}

char RightChild(BiTree T,char e)
{ /* ��ʼ����: ������T����,e��T��ĳ����� */
  /* �������: ����e���Һ��ӡ���e���Һ���,�򷵻أ��գ� */
	BiTree a;
	if (T) /* �ǿ��� */
	{
		a = Point(T, e); /* a�ǽ��e��ָ�� */
		if (a&&a->rchild) /* T�д��ڽ��e��e�����Һ��� */
			return a->rchild->data; /* ����e���Һ��ӵ�ֵ */
	}
	return Nil; /* ����������ؿ� */
}

char LeftSibling(BiTree T, char e)
{ /* ��ʼ����: ������T����,e��T��ĳ����� */
  /* �������: ����e�����ֵܡ���e��T�����ӻ������ֵ�,�򷵻أ��գ� */
	char a;
	BiTree p;
	if (T) /* �ǿ��� */
	{
		a = Parent(T, e); /* aΪe��˫�� */
		p = Point(T, a); /* pΪָ����a��ָ�� */
		if (p->lchild&&p->rchild&&p->rchild->data == e) /* p�������Һ������Һ�����e */
			return p->lchild->data; /* ����p������(e�����ֵ�) */
	}
	return Nil; /* ���ջ�û�ҵ�e�����ֵ� */
}

char RightSibling(BiTree T, char e)
{ /* ��ʼ����: ������T����,e��T��ĳ����� */
  /* �������: ����e�����ֵܡ���e��T���Һ��ӻ������ֵ�,�򷵻أ��գ� */
	char a;
	BiTree p;
	if (T) /* �ǿ��� */
	{
		a = Parent(T, e); /* aΪe��˫�� */
		p = Point(T, a); /* pΪָ����a��ָ�� */
		if (p->lchild&&p->rchild&&p->lchild->data == e) /* p�������Һ�����������e */
			return p->rchild->data; /* ����p���Һ���(e�����ֵ�) */
	}
	return Nil; /* ���ջ�û�ҵ�e�����ֵ� */
}

void InsertChild(BiTree p, int LR, BiTree c) /* �β�T���� */
{ /* ��ʼ����: ������T����, pָ��T��ĳ�����, LRΪ0��1, */
  /*           �ǿն�����c��T���ཻ��������Ϊ�� */
  /* �������: ����LRΪ0��1,����cΪT��p��ָ���������������p��ָ���� */
  /*           ԭ��������������Ϊc�������� */
	if (p) /* p���� */
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

void DeleteChild(BiTree p, int LR) /* �β�T���� */
{ /* ��ʼ����: ������T����,pָ��T��ĳ�����,LRΪ0��1 */
  /* �������: ����LRΪ0��1,ɾ��T��p��ָ������������� */
	if (p) /* p���� */
	{
		if (LR == 0) /* ɾ�������� */
			ClearBiTree(&p->lchild);
		else /* ɾ�������� */
			ClearBiTree(&p->rchild);
		
	}
	
}

void PreOrderTraverse(BiTree T, void(*Visit)(char))
{ /* ��ʼ����: ������T����,Visit�ǶԽ�������Ӧ�ú������㷨6.1���иĶ� */
  /* �������: ����ݹ����T,��ÿ�������ú���Visitһ���ҽ�һ�� */
	if (T) /* T���� */
	{
		Visit(T->data); /* �ȷ��ʸ���� */
		PreOrderTraverse(T->lchild, Visit); /* ��������������� */
		PreOrderTraverse(T->rchild, Visit); /* ���������������� */
	}
}

void InOrderTraverse(BiTree T, void(*Visit)(char))
{ /* ��ʼ����: ������T����,Visit�ǶԽ�������Ӧ�ú��� */
  /* �������: ����ݹ����T,��ÿ�������ú���Visitһ���ҽ�һ�� */
	if (T)
	{
		InOrderTraverse(T->lchild, Visit); /* ��������������� */
		Visit(T->data); /* �ٷ��ʸ���� */
		InOrderTraverse(T->rchild, Visit); /* ���������������� */
	}
}





//
void InOrderTraverse1(BiTree T, void(*Visit)(char))
{ /* ���ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú������㷨6.3 */
  /* �������������T�ķǵݹ��㷨(����ջ)����ÿ������Ԫ�ص��ú���Visit */
	SqStack S;
	InitStack(&S);
	while (T || !StackEmpty(&S))
	{
		if (T)
		{ /* ��ָ���ջ,���������� */
			Push(&S, T);
			T = T->lchild;
		}
		else
		{ /* ��ָ����ջ,���ʸ����,���������� */
			Pop(&S, &T);
			
			T = T->rchild;
		}
	}
	cout << endl;
	
}

void InOrderTraverse2(BiTree T, void(*Visit)(char))
{ /* ���ö�������洢�ṹ��Visit�Ƕ�����Ԫ�ز�����Ӧ�ú������㷨6.2 */
  /* �������������T�ķǵݹ��㷨(����ջ)����ÿ������Ԫ�ص��ú���Visit */
	SqStack S;
	BiTree p;
	InitStack(&S);
	Push(&S, T); /* ��ָ���ջ */
	while (!StackEmpty(&S))
	{
		while (GetTop(&S, &p) && p)
			Push(&S, p->lchild); /* �����ߵ���ͷ */
		Pop(&S, &p); /* ��ָ����ջ */
		if (!StackEmpty(&S))
		{ /* ���ʽ��,����һ�� */
			Pop(&S, &p);
			
			Push(&S, p->rchild);
		}
	}
	cout << endl;
	
}

void PostOrderTraverse(BiTree T, void(*Visit)(char))
{ /* ��ʼ����: ������T����,Visit�ǶԽ�������Ӧ�ú��� */
  /* �������: ����ݹ����T,��ÿ�������ú���Visitһ���ҽ�һ�� */
	if (T) /* T���� */
	{
		PostOrderTraverse(T->lchild, Visit); /* �Ⱥ������������ */
		PostOrderTraverse(T->rchild, Visit); /* �ٺ������������ */
		Visit(T->data); /* �����ʸ���� */
	}
}

void LevelOrderTraverse(BiTree T, void(*Visit)(char))
{ /* ��ʼ������������T����,Visit�ǶԽ�������Ӧ�ú��� */
  /* �������������ݹ����T(���ö���),��ÿ�������ú���Visitһ���ҽ�һ�� */
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
	cout<<"���������������(��:ab�����ո��ʾaΪ�����,bΪ�������Ķ�����)\n";
	CreateBiTree(&T);
	cout << "2";
	e1 = Root(T);
	cout << "1";
	if (e1 != Nil)

		cout << "�������ĸ�Ϊ: \n" << e1;
	else
		cout << "���գ��޸�\n" << endl;
	int a, b, c;
	cout << "��ѡ������Ҫ��ɵĲ�����1.����ݹ����������  2.����ǵݹ����������1 3.����ǵݹ����������2" << endl;
	cout << "                         4.�����ݹ���������� 5.����ݹ����������\n";
	cin >> a;
	switch (a)
	{
	case 1:
		printf("����ݹ����������:\n");
		InOrderTraverse(T, visitT);
		break;
	case 2:
		printf("\n����ǵݹ����������:\n");
		InOrderTraverse1(T, visitT);
		break;
	case 3:
		printf("����ǵݹ����������(��һ�ַ���):\n");
		InOrderTraverse2(T, visitT);
		break;
	case 4:
		printf("����ݹ����������:\n");
		PostOrderTraverse(T, visitT);
		break;
	case 5:
		printf("\n�������������:\n");
		LevelOrderTraverse(T, visitT);
		break;
	}

	printf("������һ������ֵ: ");
	cin >> e1;
	T2 = Point(T, e1);
	printf("���ı�˽���ֵ����������ֵ: ");
	cin >> e2;

	Assign(T2, e2);
	printf("�������������:\n");
	LevelOrderTraverse(T, visitT);
	e1 = Parent(T, e2);
	if (e1 != Nil)

		printf("%c��˫����%c\n", e2, e1);
	else
		printf("%cû��˫��\n", e2);
	e1 = LeftChild(T, e2);
	if (e1 != Nil)

		printf("%c��������%c\n", e2, e1);

	else
		printf("%cû������\n", e2);
	e1 = RightChild(T, e2);
	if (e1 != Nil)
		printf("%c���Һ�����%c\n", e2, e1);
	else
		printf("%cû���Һ���\n", e2);
	e1 = LeftSibling(T, e2);
	if (e1 != Nil)
		printf("%c�����ֵ���%c\n", e2, e1);

	else
		printf("%cû�����ֵ�\n", e2);
	e1 = RightSibling(T, e2);
	if (e1 != Nil)
		printf("%c�����ֵ���%c\n", e2, e1);
	else
		printf("%cû�����ֵ�\n", e2);
	system("pause");


}