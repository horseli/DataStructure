#include<iostream>
#include<malloc.h> 
#include<stdio.h>
#include<process.h>
#include<math.h> 
using namespace std;
typedef struct
{
	double co;//ϵ��
	int ep;//ָ��
}term;

struct LNode//����ʽ����
{
	term date;
	struct LNode*next;
};
typedef struct LNode* LinkList;

void IniLode(LinkList&L)//��ʼ������
{
	L = (LNode*)malloc(sizeof(LNode));
	if (!L) exit(0);
	L->next = NULL;
}
int ListLength(LinkList L)//����ʽ����
{
	LinkList p = L->next;
	int j = 0;
	for (; p; p = p->next)
		j++;
	return j;
}
void ShowList(LinkList L)//����չʾ�˶���ʽ
{
	LinkList p = L->next,q=p->next;

	for (int j = 1; j <= ListLength(L); j++, p = p->next)
	{
		char c='+';//�����������
		int w = 0;
		//�����Դ���
		if (p->date.co == 1)//��ϵ��Ϊ1��-1ʱʡ��
		{
			if (p->date.ep == 1)
				cout << "x";
			else if (p->date.ep == 0)
				cout << "1";
			else  cout << "x^" << p->date.ep;
			w = 1;
		}
		if (p->date.co == -1)
		{
			if (p->date.ep == 1)
				cout << "-x";
			else if (p->date.ep == 0)
				cout << "-1";
			else  cout << "-x^" << p->date.ep;
			w = 1;
		}
		if (p->date.ep == 0 && p->date.co != 1 && p->date.co != -1)
		{
			cout << p->date.co;
			w = 1;
		}
		if (p->date.ep == 1 && p->date.co != 1 && p->date.co != -1)
		{
			cout << p->date.co<<"*x";
			w = 1;
		}
		if(w==0) cout <<p->date.co<< "*x^" << p->date.ep;
		if (p->next&&p->next->date.co > 0)//��pָ����һ��Ϊ������pָ����һ������Ϊ��ʱ���+
			cout<<c ;
	}
	cout << endl;
}
void InsertElem(LNode*&L, int i, term e)   //�ڵ�iλ����
{
	LNode*s;
	s = (LinkList)malloc(sizeof(LNode));
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
void IniList(LinkList &L)//��ʼ������ʽ
{
	IniLode(L);
	int n;
	cout << "���������ʽ������" << endl;
	cin >> n;
	term e ;
	cout << "�������ʽϵ����ָ��" << endl;
	for (int i = 0; i < n; i++)
	{
		cin >> e.co >> e.ep;
		InsertElem(L, i + 1, e);
	}
	cout << "�������ʽΪ:";
	ShowList(L);
	cout << endl;
}
																										
term Getdate(LinkList q)//��ȡq��dateԪ��
{
	return q->date;
}
void Setdate(LinkList&q, term e)//����q��Ԫ��ֵ
{
	q->date = e;
}
void InsertPly(LinkList qa,LinkList qb)//��qb���뵽qa֮��
{
	qb->next = qa->next;
	qa->next = qb;
}


void SortList(LinkList L)//������ʽ��ָ����С ��С������������
{
	LinkList p = L->next, q = p->next;
	int n = ListLength(L);
	term *a = new term[n];//��̬�����������
	for (int i = 0; i < ListLength(L); i++)
	{
		a[i] = p->date;
		p = p->next;
	}
	term t;
	for (int i = 0; i < n - 1; i++)//ð������
	{
		int w = 0;
		for (int j = 0; j < n - i - 1; j++)
		{
			if (a[j].ep > a[j + 1].ep)
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

void Plyadd(LinkList La, LinkList Lb)//a��b����ʽ��� ��a�ӵ�b
{
	/*�Ȱ�����Ķ���ʽ����*/
	SortList(La);
	SortList(Lb);
	LinkList p = La->next, q = Lb->next, ha = La, hb = Lb;
	for (; p&&q;)
	{
		term&a = p->date, &b = q->date;//�����Ըı�ʵ��
		if (a.ep > b.ep)  //ǰ��
		{
			LinkList m = q->next, n = q;
			q->next = ha->next;
			ha->next = q;
			hb = hb->next;
			ha = q;
			q = m;
			continue;//continue�ص���㣡����
		}
		if (a.ep == b.ep)//��Ӳ�ͬʱ����
		{
			a.co += b.co;
			if (!a.co)
			{
				LinkList a1 = q, b1 = p;
				p = p->next;
				q = q->next;
				delete(a1);
				delete(b1);
			}//�����Դ��룬���Ϊ0ʱ

			else {
				ha = ha->next;
				p = p->next;
				hb = hb->next;
				q = q->next;
			}
			continue;
		}
		if (a.ep < b.ep)//La����
		{
			ha = ha->next;
			p = p->next;
			continue;
		}
	}
	if (q)
	{
		ha->next = q;
	}
}
LinkList Minus(LinkList L)//ȡ�෴�� Minus(LinkList L)//ȡ�෴��
{
	int len = ListLength(L);
	LinkList p = L->next;
	for (;p;p=p->next)
	{
		p->date.co = -p->date.co;
	}
	return L;
}
void Plysbtract(LinkList La, LinkList Lb)//���
{
	Plyadd(La, Minus(Lb));
	cout << "=";
}
void Plymulti(LinkList La, LinkList Lb)//���
{
	int lena = ListLength(La), lenb = ListLength(Lb);
	LinkList*N = new LinkList[lena];//��̬���齫�˷���Ϊ�ӷ���������
	LinkList p = La->next;
	for (int i = 0; i < lena; i++)
	{
		IniLode(N[i]);
		for (int j = 0; j < lenb; j++)
		{
			LinkList q=Lb->next;

			term temp;
			temp.co = p->date.co*q->date.co;
			temp.ep = p->date.ep+q->date.ep;
			q = q->next;
			InsertElem(N[i], j + 1, temp);
		}
		p = p->next;
	}
	for (int i = 0; i < lena-1; i++)//������
	{
		 Plyadd(N[i + 1], N[i]);
	}
	ShowList(N[lena - 1]);
}
int main()
{
	while (1)
	{
		cout << "���ȳ�ʼ����������ʽA��B" << endl;
		LinkList L1, L2;
		IniLode(L1), IniLode(L2);
		cout << "����ʽ�������ʽʾ�����£�\n" << "����2*x^2+x^3 ��Ӧ���� 2 2 1 3" << endl;
		cout << "A��ʼ����\n";
		IniList(L1);
		cout << "B��ʼ����\n";
		IniList(L2);
		cout << "��ѡ������Ҫ��ɵĲ���\n���磬��ִ�� A-B ������������A-B " << endl;
		char a, b, c;
		cin >> a >> b >> c;
		switch (a)
		{
		case'A':switch (b)
		{
		case'+': Plyadd(L1, L2);
			ShowList(L1);
			break;
		case'-':Plysbtract(L1, L2);
			ShowList(L1);
			break;
		case'*':Plymulti(L1, L2);
			break;
		}break;
		case'B':switch (b)
		{
		case'+':Plyadd(L1, L2);
			ShowList(L1);
			break;
		case'-':Plysbtract(L2, L1);
			ShowList(L2);
			break;
		case'*':Plymulti(L1, L2);
			break;
		}
		}
		cout << endl;
	}
}
