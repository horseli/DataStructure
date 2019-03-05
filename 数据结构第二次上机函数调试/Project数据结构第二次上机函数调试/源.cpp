#include<iostream>
#include<string.h>
#include<ctype.h>
#include<malloc.h> /* malloc()等 */
#include<limits.h> /* INT_MAX等 */
#include<stdio.h> /* EOF(=^Z或F6),NULL */
#include<stdlib.h> /* atoi() */
#include<io.h> /* eof() */
#include<math.h> /* floor(),ceil(),abs() */
#include<process.h> /* exit() */
using namespace std;
typedef struct LNode* LinkList;
struct LNode
{
	int date;
	LNode*next;

};

void IniList(LinkList&L)
{
	L = (LNode*)malloc(sizeof(LNode));
	if (!L) exit(0);
	L->next = NULL;
}
int GetElem(LinkList L, int i)
{
	int j = 1;
	LinkList p = L->next;
	for (; p&&j < i; j++)
		p = p->next;
	if (!p || j > i)
	{
		cout << "链表中无此数" << endl;
		exit(0);
	}
	return p->date;
}
void InsertElem(LNode*&L, int i, int e)   //在第i位插入
{
	LNode*s;
	s = (LinkList)malloc(sizeof(struct LNode));
	if (!s) exit(0);
	s->date = e;
	int j = 0;
	LinkList p = L;
	for (; j < i - 1 && p; j++)
	{
		p = p->next;
	}
	s->next = p->next;
	p->next = s;

}
int ListLength(LinkList L)
{
	LinkList p = L->next;
	int j = 0;
	for (; p; p = p->next)
		j++;
	return j;
}
void DeleteList(LinkList L, int i, int&e)
{
	LinkList p = L;
	if (i > ListLength(L))
		cout << "链表中无此元素" << endl;
	int j = 0;
	for (; j < i - 1 && p; j++)
		p = p->next;
	LinkList q = p->next;
	e = q->date;
	p->next = q->next;
	cout << "被删除元素为" << e << endl;
	free(q);
}
void ShowList(LinkList L)
{
	LinkList p = L->next;
	cout << "该链表所含元素有：" << endl;
	for (int j = 1; j <= ListLength(L); j++,p=p->next)
	{
		cout << p->date << " ";
	}
}
void LocateList(LinkList L, int e)
{
	LinkList p = L;
	int j = 0;
	for (; j < ListLength(L) && p->next->date != e; j++, p = p->next);
	if (j >= ListLength(L))
	{
		cout << "链表中无此元素" << endl;
		return;
	}
	cout << "该元素位于链表的第" << j + 1 << "位" << endl;
}

void SortList1(LinkList L)
{
	LinkList p = L->next, q = p->next;
	int n = ListLength(L);
	int *a = new int[n];
	for (int i = 0; i < ListLength(L); i++)
	{
		a[i] = p->date;
		p = p->next;
	}
	int t;
	for (int i = 0; i < n-1; i++)
	{
		int w = 0;
		for (int j = 0; j < n - i-1; j++)
		{
			if (a[j] > a[j + 1])
			{
				t = a[j];
				a[j] = a[j + 1];
				a[j + 1] = t;
				w = 1;
			}
		}
		if (w = 0)
			break;
	}
	p = L->next;
	for (int i = 0; i < n; i++)
	{
		p->date = a[i];
		p = p->next;
	}
}
void SortList2(LinkList L)
{
	LinkList p = L->next, q = p->next;
	int n = ListLength(L);
	int *a = new int[n];
	for (int i = 0; i < ListLength(L); i++)
	{
		a[i] = p->date;
		p = p->next;
	}
	int t;
	for (int i = 0; i < n-1; i++)
	{
		int w = 0;
		for (int j = n - 1; j >0; j--)
		{
			if (a[j] > a[j - 1])
			{
				t = a[j];
				a[j] = a[j-1];
				a[j-1] = t;
				w = 1;
			}
		}
		if (w = 0)
			break;
	}
	p = L->next;
	for (int i = 0; i < n; i++)
	{
		p->date = a[i];
		p = p->next;
	}
}
void Union(LinkList La, LinkList Lb,LinkList Lc)
{
	LinkList p = La->next;
	LinkList q = Lb->next;
	int len_a = ListLength(La), len_b = ListLength(Lb),len_c=ListLength(Lc);
	for (int t = 0; t < len_b; t++, q = q->next)
	{
		InsertElem(Lc, ++len_c, q->date);
	}
	q = Lb->next;
	for (int i = 0; i < len_a; i++, p = p->next)
	{
		int t = 0;
		for (int j = 0; j < len_b; j++, q = q->next)
		{
			if (q->date == p->date)
			{
				t = 1;
				break;
			}
		}
		q = Lb->next;
		if (t == 0)
			InsertElem(Lc, ++len_c, p->date);
	}

}
void AddUnion(LinkList La, LinkList Lb, LinkList Lc)
{
	LinkList p = La->next, q = Lb->next, s = Lc->next;
	SortList1(La);
	SortList1(Lb);
	int len_a = ListLength(La), len_b = ListLength(Lb), len_c = ListLength(Lc);
	int i, j;
	while (p&&q)
	{
		if (p->date <= q->date)
		{
			InsertElem(Lc, ++len_c, p->date);
			p = p->next;
		}
		else { InsertElem(Lc, ++len_c, q->date);
		q = q->next;
		}
	}
	while (p) { InsertElem(Lc, ++len_c, p->date);
	p = p->next;
	}
	while (q) { InsertElem(Lc, ++len_c, q->date); 
	q = q->next;
	}
}
int main()
{
	
	
	LinkList L, p;
	IniList(L);
	int i, x;
	cout << "元素个数" << endl;

	cin >> i;

	cout << "元素为" << endl;

	for (int j = 0; j < i; j++)
	{
		cin >> x;
		InsertElem(L, j + 1, x);
	}
	 p = L->next;
	
	
	 cout << "归并" << endl;

	LinkList Lc;
	IniList(Lc);
	cout << "元素个数" << endl;

	cin >> i;

	cout << "元素为" << endl;


	for (int j = 0; j < i; j++)
	{
		cin >> x;
		InsertElem(Lc, j + 1, x);
	}
	LinkList Lx;
	IniList(Lx);
	
	AddUnion(L, Lc, Lx);
	ShowList(Lx);

	Union(L, Lc,Lx);
	ShowList(Lx);

	cout << "正序排序" << endl;
	SortList1(L);
	ShowList(L);
	cout << endl;
	cout << "反序排序" << endl;
	SortList2(L);
	ShowList(L);


	cin >> x;
	LocateList(L, x);
	cout << "删除第几位元素" << endl;
	cin >> i;
	DeleteList(L, i, x);
	ShowList(L);
	cout << "插入的元素是位于第几位哪个数" << endl;
	cin >> i >> x;
	InsertElem(L, i, x);
	p = L->next;
	p = p->next;
	cout << p->next->date << endl;
	ShowList(L);
	
	system("pause");
}