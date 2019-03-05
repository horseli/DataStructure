#include<iostream>
#include<string.h>
#include<ctype.h>
#include<malloc.h> /* malloc()�� */
#include<limits.h> /* INT_MAX�� */
#include<stdio.h> /* EOF(=^Z��F6),NULL */
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
		cout << "�������޴���" << endl;
		exit(0);
	}
	return p->date;
}
void InsertElem(LNode*&L, int i, int e)   //�ڵ�iλ����
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
		cout << "�������޴�Ԫ��" << endl;
	int j = 0;
	for (; j < i - 1 && p; j++)
		p = p->next;
	LinkList q = p->next;
	e = q->date;
	p->next = q->next;
	cout << "��ɾ��Ԫ��Ϊ" << e << endl;
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
		cout << "�������޴�Ԫ��" << endl;
		return;
	}
	cout << "��Ԫ��λ������ĵ�" << j + 1 << "λ" << endl;
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
	cout << "�� ӭ �� �� �� �� �� ����" << endl;
	cout << "- - - - - - - -  - - -  - - - - " << endl;
	cout << "�����ȳ�ʼ��һ��˳���La" << endl;
	IniList(La);
	int el, x, i = 1, m = 0;
	cout << "La�����ݸ���Ϊ��";
	cin >> x;
	cout << endl;
	cout << "La��Ԫ��Ϊ��";
	while (i <= x)
	{
		cin >> el;
		InsertElem(La, i, el);
		i++;

	}
	cout << endl;
	while (1)
	{
		cout << "��ѡ������Ҫ��ɵĲ�����" << endl;
		cout << "1.����Ԫ��\t" << "2.ɾ��Ԫ��\n" << "3.����Ԫ��\t" << "4.����Ԫ��\n" << "5.˳������\t" << "6,��������\n " << "7.������Lb\n";
		cout << endl;
		int s1;
		cin >> s1;
		if (s1 > 7 || s1 < 1)
		{
			cout << "�������" << endl;

		}
		switch (s1)
		{
		case 1: {
			cout << "�ڱ��__��Ԫ��ǰ����Ԫ��__:";
			cin >> i >> el;
			InsertElem(La, i, el);
			cout << "�����ı�Ϊ��" << endl;
			ShowList(La);
			break;
		}
		case 2: {
			cout << "ɾ����__��Ԫ�أ�";
			cin >> i;
			int ee;
			DeleteList(La, i, ee);
			cout << "ɾ����ı�Ϊ��" << endl;
			ShowList(La);
			break;
		}
		case 3:
		{
			cout << "��Ҫ���ҵ�Ԫ��Ϊ��" << endl;
			cin >> i;
			LocateList(La, i);
			break;
		}
		case 4:
		{
			cout << "����ȫ��Ԫ��Ϊ��" << endl;
			ShowList(La);
			break;
		}
		case 5:
		{
			SortList1(La);
			cout << "��С������������Ԫ��Ϊ��" << endl;
			ShowList(La);
			break;
		}
		case 6:
		{
			SortList2(La);
			cout << "�Ӵ�С��������Ԫ��Ϊ��" << endl;
			ShowList(La);
			break;
		}
		case 7:
		{

			LinkList Lb;
			cout << "�����ȳ�ʼ��һ��˳���Lb" << endl;
			IniList(Lb);
			cout << "Lb������Ԫ�ظ���Ϊ��";
			int el, i = 1, x;
			cin >> x;
			cout << endl;
			cout << "Lb��Ԫ��Ϊ��";
			while (i <= x)
			{
				cin >> el;
				InsertElem(Lb, i, el);
				i++;
			}
			cout << endl;
			cout << "��ѡ������Ҫ��ɵĲ�����" << endl;
			cout << "1.����Ԫ��\t" << "2.ɾ��Ԫ��\n" << "3.����Ԫ��\t" << "4.����Ԫ��\n" << "5.˳������\t" << "6,��������\n" << "7.�鲢��La��Lb  \t" << "8.�Ͳ���La��Lb\n";
			cout << endl;

			int s1;
			cin >> s1;
			if (s1 > 8 || s1 < 0)
			{
				cout << "�������" << endl;
				exit(0);
			}
			switch (s1)
			{
			case 1: {
				cout << "�ڱ��__��Ԫ��ǰ����Ԫ��__:";
				cin >> i >> el;
				InsertElem(Lb, i, el);
				cout << "�����ı�Ϊ��" << endl;
				ShowList(Lb);
				break;
			}
			case 2: {
				cout << "ɾ����__��Ԫ�أ�";
				cin >> i;
				int e;
				DeleteList(Lb, i, e);
				break;
			}
			case 3:
			{
				cout << "��Ҫ���ҵ�Ԫ��Ϊ��" << endl;
				cin >> i;
				LocateList(Lb, i);
				break;
			}
			case 4:
			{
				cout << "����ȫ��Ԫ��Ϊ��" << endl;
				ShowList(Lb);
				break;
			}
			case 5:
			{
				SortList1(Lb);
				cout << "��С������������Ԫ��Ϊ��" << endl;
				ShowList(Lb);
				break;
			}
			case 6:
			{
				SortList2(Lb);
				cout << "�Ӵ�С��������Ԫ��Ϊ��" << endl;
				ShowList(Lb);
				break;
			}
			case 7:
			{
				cout << "��ѡ����Ҫ���еĲ������ѱ�La�鲢����Lb(b) / �ѱ�Lb�鲢��La��a��/�鲢���±�Lc(c)" << endl;
				char s2;
				cin >> s2;
				switch (s2)
				{
				case 'b': {Union(La, Lb, Lb);
					cout << "�鲢��ı�LbΪ��" << endl;
					ShowList(Lb);
					cout << endl;
					break; }
				case 'a': {Union(Lb, La, La);
					cout << "�鲢��ı�LaΪ��" << endl;
					ShowList(La);
					cout << endl;
					break; }
				case'c':
					Union(La, Lb, Lc);
					cout << "�鲢��ı�LcΪ��" << endl;
					ShowList(Lc);
					cout << endl;
					break;
				}
				break;
			}
			case 8:
			{
				cout << "��ѡ����Ҫ���еĲ������ѱ�La�Ͳ�����Lb(a) / �ѱ�Lb�Ͳ���La��b��/ �Ͳ����±�Lc(c)" << endl;
				char s2;
				cin >> s2;
				switch (s2)
				{
				case 'b': {AddUnion(La, Lb, La);

					cout << "�Ͳ���ı�LaΪ��" << endl;
					La = Lc;
					ShowList(La);
					cout << endl;
					break; }
				case 'a': {AddUnion(Lb, La, Lb);
					cout << "�Ͳ���ı�LbΪ��" << endl;
					Lb = Lc;
					ShowList(Lb);
					cout << endl;
					break; }
				case 'c': {AddUnion(Lb, La, Lc);
					cout << "�Ͳ���ı�LcΪ��" << endl;
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
