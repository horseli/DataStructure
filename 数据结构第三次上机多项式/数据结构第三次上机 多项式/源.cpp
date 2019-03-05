#include<iostream>
#include<malloc.h> 
#include<stdio.h>
#include<process.h>
#include<math.h> 
using namespace std;
typedef struct
{
	double co;//系数
	int ep;//指数
}term;

struct LNode//多项式链表
{
	term date;
	struct LNode*next;
};
typedef struct LNode* LinkList;

void IniLode(LinkList&L)//初始化链表
{
	L = (LNode*)malloc(sizeof(LNode));
	if (!L) exit(0);
	L->next = NULL;
}
int ListLength(LinkList L)//多项式项数
{
	LinkList p = L->next;
	int j = 0;
	for (; p; p = p->next)
		j++;
	return j;
}
void ShowList(LinkList L)//遍历展示此多项式
{
	LinkList p = L->next,q=p->next;

	for (int j = 1; j <= ListLength(L); j++, p = p->next)
	{
		char c='+';//输出的正负号
		int w = 0;
		//美观性代码
		if (p->date.co == 1)//当系数为1和-1时省略
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
		if (p->next&&p->next->date.co > 0)//当p指针下一个为正数且p指针下一个数不为空时输出+
			cout<<c ;
	}
	cout << endl;
}
void InsertElem(LNode*&L, int i, term e)   //在第i位插入
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
void IniList(LinkList &L)//初始化多项式
{
	IniLode(L);
	int n;
	cout << "请输入多项式的项数" << endl;
	cin >> n;
	term e ;
	cout << "输入多项式系数和指数" << endl;
	for (int i = 0; i < n; i++)
	{
		cin >> e.co >> e.ep;
		InsertElem(L, i + 1, e);
	}
	cout << "输入多项式为:";
	ShowList(L);
	cout << endl;
}
																										
term Getdate(LinkList q)//获取q的date元素
{
	return q->date;
}
void Setdate(LinkList&q, term e)//设置q的元素值
{
	q->date = e;
}
void InsertPly(LinkList qa,LinkList qb)//将qb插入到qa之后
{
	qb->next = qa->next;
	qa->next = qb;
}


void SortList(LinkList L)//将多项式按指数大小 从小到大升序排序
{
	LinkList p = L->next, q = p->next;
	int n = ListLength(L);
	term *a = new term[n];//动态数组便于排序
	for (int i = 0; i < ListLength(L); i++)
	{
		a[i] = p->date;
		p = p->next;
	}
	term t;
	for (int i = 0; i < n - 1; i++)//冒泡排序法
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

void Plyadd(LinkList La, LinkList Lb)//a与b多项式相加 将a加到b
{
	/*先把输入的多项式排序*/
	SortList(La);
	SortList(Lb);
	LinkList p = La->next, q = Lb->next, ha = La, hb = Lb;
	for (; p&&q;)
	{
		term&a = p->date, &b = q->date;//引用以改变实参
		if (a.ep > b.ep)  //前插
		{
			LinkList m = q->next, n = q;
			q->next = ha->next;
			ha->next = q;
			hb = hb->next;
			ha = q;
			q = m;
			continue;//continue回到起点！！！
		}
		if (a.ep == b.ep)//相加并同时后移
		{
			a.co += b.co;
			if (!a.co)
			{
				LinkList a1 = q, b1 = p;
				p = p->next;
				q = q->next;
				delete(a1);
				delete(b1);
			}//美观性代码，相加为0时

			else {
				ha = ha->next;
				p = p->next;
				hb = hb->next;
				q = q->next;
			}
			continue;
		}
		if (a.ep < b.ep)//La后移
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
LinkList Minus(LinkList L)//取相反数 Minus(LinkList L)//取相反数
{
	int len = ListLength(L);
	LinkList p = L->next;
	for (;p;p=p->next)
	{
		p->date.co = -p->date.co;
	}
	return L;
}
void Plysbtract(LinkList La, LinkList Lb)//相减
{
	Plyadd(La, Minus(Lb));
	cout << "=";
}
void Plymulti(LinkList La, LinkList Lb)//相乘
{
	int lena = ListLength(La), lenb = ListLength(Lb);
	LinkList*N = new LinkList[lena];//动态数组将乘法变为加法保存数据
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
	for (int i = 0; i < lena-1; i++)//逐次相加
	{
		 Plyadd(N[i + 1], N[i]);
	}
	ShowList(N[lena - 1]);
}
int main()
{
	while (1)
	{
		cout << "请先初始化两个多项式A和B" << endl;
		LinkList L1, L2;
		IniLode(L1), IniLode(L2);
		cout << "多项式的输入格式示例如下：\n" << "输入2*x^2+x^3 则应输入 2 2 1 3" << endl;
		cout << "A初始化：\n";
		IniList(L1);
		cout << "B初始化：\n";
		IniList(L2);
		cout << "请选择您想要完成的操作\n例如，想执行 A-B 操作，则输入A-B " << endl;
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
