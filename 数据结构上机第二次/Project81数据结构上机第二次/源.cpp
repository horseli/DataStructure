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
	for (int j = 1; j <= ListLength(L); j++, p = p->next)
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
	for (int i = 0; i < n - 1; i++)
	{
		int w = 0;
		for (int j = 0; j < n - i - 1; j++)
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
	for (int i = 0; i < n - 1; i++)
	{
		int w = 0;
		for (int j = n - 1; j >0; j--)
		{
			if (a[j] > a[j - 1])
			{
				t = a[j];
				a[j] = a[j - 1];
				a[j - 1] = t;
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
void Union(LinkList La, LinkList Lb, LinkList Lc)
{
	LinkList p = La->next;
	LinkList q = Lb->next;
	int len_a = ListLength(La), len_b = ListLength(Lb), len_c = ListLength(Lc);
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
		else {
			InsertElem(Lc, ++len_c, q->date);
			q = q->next;
		}
	}
	while (p) {
		InsertElem(Lc, ++len_c, p->date);
		p = p->next;
	}
	while (q) {
		InsertElem(Lc, ++len_c, q->date);
		q = q->next;
	}
}
int main()
{

	LinkList La;
	LinkList Lc;
	IniList(Lc);
	cout << "欢 迎 来 到 链 表 操 作！" << endl;
	cout << "- - - - - - - -  - - -  - - - - " << endl;
	cout << "请您先初始化一个顺序表La" << endl;
	IniList(La);
	int el, x, i = 1, m = 0;
	cout << "La的数据个数为：";
	cin >> x;
	cout << endl;
	cout << "La各元素为：";
	while (i <= x)
	{
		cin >> el;
		InsertElem(La, i, el);
		i++;

	}
	cout << endl;
	while (1)
	{
		cout << "请选择您想要完成的操作：" << endl;
		cout << "1.插入元素\t" << "2.删除元素\n" << "3.查找元素\t" << "4.遍历元素\n" << "5.顺序排序\t" << "6,反序排序\n " << "7.创建表Lb\n";
		cout << endl;
		int s1;
		cin >> s1;
		if (s1 > 7 || s1 < 1)
		{
			cout << "输入错误" << endl;

		}
		switch (s1)
		{
		case 1: {
			cout << "在表第__个元素前插入元素__:";
			cin >> i >> el;
			InsertElem(La, i, el);
			cout << "插入后的表为：" << endl;
			ShowList(La);
			break;
		}
		case 2: {
			cout << "删除第__个元素：";
			cin >> i;
			int ee;
			DeleteList(La, i, ee);
			cout << "删除后的表为：" << endl;
			ShowList(La);
			break;
		}
		case 3:
		{
			cout << "您要查找的元素为：" << endl;
			cin >> i;
			LocateList(La, i);
			break;
		}
		case 4:
		{
			cout << "表中全部元素为：" << endl;
			ShowList(La);
			break;
		}
		case 5:
		{
			SortList1(La);
			cout << "从小到大排序后表中元素为：" << endl;
			ShowList(La);
			break;
		}
		case 6:
		{
			SortList2(La);
			cout << "从大到小排序后表中元素为：" << endl;
			ShowList(La);
			break;
		}
		case 7:
		{

			LinkList Lb;
			cout << "请您先初始化一个顺序表Lb" << endl;
			IniList(Lb);
			cout << "Lb的数据元素个数为：";
			int el, i = 1, x;
			cin >> x;
			cout << endl;
			cout << "Lb各元素为：";
			while (i <= x)
			{
				cin >> el;
				InsertElem(Lb, i, el);
				i++;
			}
			cout << endl;
			cout << "请选择您想要完成的操作：" << endl;
			cout << "1.插入元素\t" << "2.删除元素\n" << "3.查找元素\t" << "4.遍历元素\n" << "5.顺序排序\t" << "6,反序排序\n" << "7.归并表La和Lb  \t" << "8.和并表La和Lb\n";
			cout << endl;

			int s1;
			cin >> s1;
			if (s1 > 8 || s1 < 0)
			{
				cout << "输入错误" << endl;
				exit(0);
			}
			switch (s1)
			{
			case 1: {
				cout << "在表第__个元素前插入元素__:";
				cin >> i >> el;
				InsertElem(Lb, i, el);
				cout << "插入后的表为：" << endl;
				ShowList(Lb);
				break;
			}
			case 2: {
				cout << "删除第__个元素：";
				cin >> i;
				int e;
				DeleteList(Lb, i, e);
				break;
			}
			case 3:
			{
				cout << "您要查找的元素为：" << endl;
				cin >> i;
				LocateList(Lb, i);
				break;
			}
			case 4:
			{
				cout << "表中全部元素为：" << endl;
				ShowList(Lb);
				break;
			}
			case 5:
			{
				SortList1(Lb);
				cout << "从小到大排序后表中元素为：" << endl;
				ShowList(Lb);
				break;
			}
			case 6:
			{
				SortList2(Lb);
				cout << "从大到小排序后表中元素为：" << endl;
				ShowList(Lb);
				break;
			}
			case 7:
			{
				cout << "请选择您要进行的操作：把表La归并到表Lb(b) / 把表Lb归并到La（a）/归并到新表Lc(c)" << endl;
				char s2;
				cin >> s2;
				switch (s2)
				{
				case 'b': {Union(La, Lb, Lb);
					cout << "归并后的表Lb为：" << endl;
					ShowList(Lb);
					cout << endl;
					break; }
				case 'a': {Union(Lb, La, La);
					cout << "归并后的表La为：" << endl;
					ShowList(La);
					cout << endl;
					break; }
				case'c':
					Union(La, Lb, Lc);
					cout << "归并后的表Lc为：" << endl;
					ShowList(Lc);
					cout << endl;
					break;
				}
				break;
			}
			case 8:
			{
				cout << "请选择您要进行的操作：把表La和并到表Lb(a) / 把表Lb和并到La（b）/ 和并到新表Lc(c)" << endl;
				char s2;
				cin >> s2;
				switch (s2)
				{
				case 'b': {AddUnion(La, Lb, La);

					cout << "和并后的表La为：" << endl;
					La = Lc;
					ShowList(La);
					cout << endl;
					break; }
				case 'a': {AddUnion(Lb, La, Lb);
					cout << "和并后的表Lb为：" << endl;
					Lb = Lc;
					ShowList(Lb);
					cout << endl;
					break; }
				case 'c': {AddUnion(Lb, La, Lc);
					cout << "和并后的表Lc为：" << endl;
					ShowList(Lc);
					cout << endl;
					break; }
				}
			}



			}

		}


		}
		cout << endl;
		cout << endl;
	}
		system("pause");
	}
