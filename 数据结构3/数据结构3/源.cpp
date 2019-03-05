

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
#define true  1
#define false 0
#define ok    1
#define error 0
typedef int status;

#define max_name 10  /* 顶点字符串的最大长度+1 */
#define max_info 20  /* 相关信息字符串的最大长度+1 */
typedef int vrtype;
typedef char infotype;
typedef char vertextype[max_name];   //？为啥可以这样子命名// 

#define infinity  INT_MAX /* 用整型最大值代替∞ */
#define max_vertex_num 20 /* 最大顶点个数 */
typedef enum { DG, DN, UDG, UDN } graphkind; /* {有向图,有向网,无向图,无向网} */
typedef struct
{
	vrtype adj; /* 顶点关系类型,对无权图，用1(是)或0(否)表示相邻否;对带权图，则为权值类型 */
	infotype *info; /* 该弧相关信息的指针(可无) */
}arccell, adjmatrix[max_vertex_num][max_vertex_num];
typedef struct
{
	vertextype vexs[max_vertex_num]; /* 顶点向量 */
	adjmatrix arcs;       /* 邻接矩阵 */
	int vexnum, arcnum;    /* 图的当前顶点数和弧数 */
	int kind;       /* 图的种类标志 */
}mgraph;

status visit(vertextype i)
{
	cout << i;
	return ok;
}
/* 初始条件:图g存在,u和g中顶点有相同特征 */
/* 操作结果:若g中存在顶点u,则返回该顶点在图中位置;否则返回-1 */
int locatevex(mgraph g, vertextype u)
{
	int i;
	for (i = 0; i<g.vexnum; i++)
		if (strcmp(u, g.vexs[i]) == 0)
			return i;
	return -1;
}

/* 采用数组(邻接矩阵)表示法,构造有向图g*/
status createDG(mgraph &g)
{
	int i, j, k, l, incinfo;
	char s[max_info], *info;
	vertextype va, vb;
	cout << "请输入有向图的顶点数、弧数，弧是否包含其他信息（1:是 2:否）\n";
	cin >> g.vexnum >> g.arcnum >> incinfo;
	cout << g.vexnum << "个顶点的值（" << max_name << "个字符以内)\n";
	for (i = 0; i<g.vexnum; i++)  //构造顶点向量 	
		cin >> g.vexs[i];
	for (i = 0; i<g.vexnum; i++) //初始化矩阵 
		for (j = 0; j<g.vexnum; j++)
		{
			g.arcs[i][j].adj = 0;   //图 
			g.arcs[i][j].info = NULL;
		}
	cout << "请输入" << g.arcnum << "条弧的弧尾、弧头(以空格作为间隔):\n";
	for (k = 0; k<g.arcnum; k++)
	{
		cin >> va >> vb;
		cin.get(); //吸收回车符
		i = locatevex(g, va);
		j = locatevex(g, vb);
		g.arcs[i][j].adj = 1;
		if (incinfo)
		{
			cout << "请输入该弧的相关信息（" << max_info << "个字符）";
			gets(s);
			l = strlen(s);
			if (l)
			{
				info = new char[l + 1];
				strcpy(info, s);
				g.arcs[i][j].info = info;
			}
		}
	}
	g.kind = DG;
	return ok;
}

status createDN(mgraph &g)
{
	int i, j, k, w, incinfo;
	char s[max_info], *info;
	vertextype va, vb;
	cout << "请输入有向网的顶点数、弧数，弧是否包含其他信息(1:是 2:否)\n";
	cin >> g.vexnum >> g.arcnum >> incinfo;
	cout << "请输入" << g.vexnum << "个顶点的值（" << max_name << "个字符）\n";
	for (i = 0; i<g.vexnum; i++)  // 构造顶点向量 
		cin >> g.vexs[i];
	for (i = 0; i<g.vexnum; i++)     // 初始化邻接矩阵 
		for (j = 0; j<g.vexnum; j++)
		{
			g.arcs[i][j].adj = infinity; //网
			g.arcs[i][j].info = NULL;
		}
	cout << "请输入" << g.arcnum << "条弧的弧尾、弧头、权值(以空格作为间隔):\n";
	for (k = 0; k<g.arcnum; k++)
	{
		cin >> va >> vb >> w;
		cin.get();//吸收回车符  
		i = locatevex(g, va);
		j = locatevex(g, vb);
		g.arcs[i][j].adj = w; //有向网 
		if (incinfo)
		{
			cout << "请输入该弧的相关信息（" << max_info << "个字符)";
			gets(s);
			w = strlen(s);
			if (w)
			{
				info = new char[w + 1];
				strcpy(info, s);
				g.arcs[i][j].info = info; //有向  
			}
		}
	}
	g.kind = DN;
	return ok;
}

/* 采用数组(邻接矩阵)表示法,构造无向图G */
status createUDG(mgraph &g)
{
	int i, j, k, l, incinfo;
	char s[max_info], *info;
	vertextype va, vb;
	cout << "请输入无向图的顶点数、边数，边是否含有其他信息（1:是 2:否)\n";
	cin >> g.vexnum >> g.arcnum >> incinfo;
	cout << "请输入" << g.vexnum << "个顶点的值（" << max_name << "个字符）\n";
	for (i = 0; i<g.vexnum; i++) /* 构造顶点向量 */
		cin >> g.vexs[i];
	for (i = 0; i<g.vexnum; i++)  /* 初始化邻接矩阵 */
		for (j = 0; j<g.vexnum; j++)
		{
			g.arcs[i][j].adj = 0;   /* 图 */
			g.arcs[i][j].info = NULL;
		}
	cout << "请输入" << g.arcnum << "条边的顶点1、顶点2(以空格作为间隔):\n";
	for (k = 0; k<g.vexnum; k++)
	{
		cin >> va >> vb;
		cin.get(); //吸收回车符 
		i = locatevex(g, va);
		j = locatevex(g, vb);
		g.arcs[i][j].adj = g.arcs[j][i].adj = 1; //无向图
		if (incinfo)
		{
			cout << "请输入该边的相关信息（" << max_info << "个字符）";
			gets(s);
			l = strlen(s);
			if (l)
			{
				info = new char[l + 1];
				strcpy(info, s);
				g.arcs[i][j].info = g.arcs[j][i].info = info;
			}
		}
	}
	g.kind = UDG;
	return ok;
}

/* 采用数组(邻接矩阵)表示法,构造无向网g。*/
status createUDN(mgraph &g)
{
	int i, j, k, w, incinfo;
	char s[max_info], *info;
	vertextype va, vb;
	cout << "请输入无向图的顶点数、边数，边是否含有其他信息（1:是 2:否)\n";
	cin >> g.vexnum >> g.arcnum >> incinfo;
	cout << "请输入" << g.vexnum << "个顶点的值（" << max_name << "个字符）\n";
	for (i = 0; i<g.vexnum; i++) /* 构造顶点向量 */
		cin >> g.vexs[i];
	for (i = 0; i<g.vexnum; i++)  /* 初始化邻接矩阵 */
		for (j = 0; j<g.vexnum; j++)
		{
			g.arcs[i][j].adj = infinity;   /* 网 */
			g.arcs[i][j].info = NULL;
		}
	cout << "请输入" << g.arcnum << "条边的顶点1、顶点2、权值(以空格作为间隔):\n";
	for (k = 0; k<g.vexnum; k++)
	{
		cin >> va >> vb >> w;
		cin.get(); //吸收回车符 
		i = locatevex(g, va);
		j = locatevex(g, vb);
		g.arcs[i][j].adj = g.arcs[j][i].adj = w; //无向网 
		if (incinfo)
		{
			cout << "请输入该边的相关信息（" << max_info << "个字符）";
			gets(s);
			w = strlen(s);
			if (w)
			{
				info = new char[w + 1];
				strcpy(info, s);
				g.arcs[i][j].info = g.arcs[j][i].info = info;
			}
		}
	}
	g.kind = UDN;
	return ok;
}

/* 采用数组(邻接矩阵)表示法,构造图g。*/
/*初始条件：V是图的顶点集，VR是图中弧的集合。
操作结果：按V和VR的定义构造图g*/
status creategraph(mgraph &g)
{
	cout << "请输入图的类型(0:有向图 1:有向网 2:无向图 3:无向网)" << endl;
	cin >> g.kind;
	switch (g.kind)
	{
	case DG:return createDG(g);  //构造有向图g 
	case DN:return createDN(g);  //构造有向网g 
	case UDG:return createUDG(g);//构造无向图g 
	case UDN:return createUDN(g);//构造无向网g 
	default:return error;
	}
}

/* 初始条件: 图g存在。操作结果: 销毁图g */
void destroygraph(mgraph&g)
{
	int i, j;
	if (g.kind <= 1)  /* 有向 */
	{
		for (i = 0; i<g.vexnum; i++)  /* 释放弧的相关信息(如果有的话) */
		{
			for (j = 0; j<g.vexnum; j++)
				if (g.arcs[i][j].adj == 1 && g.kind == 0 || g.arcs[i][j].adj != infinity&&g.kind == 1) /* 有向图的弧||有向网的弧 */
					if (g.arcs[i][j].info)  /* 有相关信息 */
					{
						delete g.arcs[i][j].info;
						g.arcs[i][j].info = NULL;
					}
		}
	}
	else  /* 无向 */
	{
		for (i = 0; i<g.vexnum; i++) /* 释放边的相关信息(如果有的话) */
			for (j = i + 1; j<g.vexnum; j++)
				if (g.arcs[i][j].adj == 1 && g.kind == 2 || g.arcs[i][j].adj != infinity&&g.kind == 3) /* 无向图的边||无向网的边 */
					if (g.arcs[i][j].info) /* 有相关信息 */
					{
						delete g.arcs[i][j].info;
						g.arcs[i][j].info = NULL;
					}
	}
	g.vexnum = 0;
	g.arcnum = 0;
}

/* 初始条件: 图g存在，v是g中某个顶点的序号。操作结果: 返回v的值 */
vertextype* getvex(mgraph g, int v)
{
	if (v >= g.vexnum || v<0)
		exit(error);
	return &g.vexs[v];
}

/*初始条件: 图g存在，v是g中某个顶点。操作结果: 对v赋新值value */
status putvex(mgraph &g, vertextype v, vertextype value)
{
	int k;
	k = locatevex(g, v); /* k为顶点v在图g中的序号 */
	if (k<0) return error;
	strcpy(g.vexs[k], value);
	return ok;
}

/* 初始条件: 图g存在,v是g中某个顶点 */
/* 操作结果: 返回v的第一个邻接顶点的序号。若顶点在g中没有邻接顶点,则返回-1 */
int firstadjvex(mgraph g, vertextype v)
{
	int i, j = 0, k;
	k = locatevex(g, v);  /* k为顶点v在图g中的序号 */
	if (g.kind == DN || g.kind == UDN) //网
		j = infinity;
	for (i = 0; i<g.vexnum; i++)
		if (g.arcs[k][i].adj != j)
			return i;
	return -1;
}

/* 初始条件: 图g存在,v是g中某个顶点,w是v的邻接顶点
操作结果: 返回v的(相对于w的)下一个邻接顶点的序号,
若w是v的最后一个邻接顶点,则返回-1 */
int nextadjvex(mgraph g, vertextype v, vertextype w)
{
	int i, j = 0, k1, k2;
	k1 = locatevex(g, v);/* k1为顶点v在图g中的序号 */
	k2 = locatevex(g, w);/* k2为顶点v在图g中的序号 */
	if (g.kind == DN || g.kind == UDN) //网
		j = infinity;
	for (i = k2 + 1; i<g.vexnum; i++)
		if (g.arcs[k1][i].adj != j)
			return i;
	return -1;
}

/* 初始条件: 图g存在,v和图g中顶点有相同特征 */
/* 操作结果: 在图g中增添新顶点v(不增添与顶点相关的弧,留待InsertArc()去做) */
void insertvex(mgraph &g, vertextype v)
{
	int i;
	strcpy(g.vexs[g.vexnum], v); /* 构造新顶点向量 */
	for (i = 0; i <= g.vexnum; i++)
	{
		if (g.kind % 2)   /* 网 */
		{
			g.arcs[g.vexnum][i].adj = infinity;/* 初始化该行邻接矩阵的值(无边或弧) */
			g.arcs[i][g.vexnum].adj = infinity;/* 初始化该列邻接矩阵的值(无边或弧) */
		}
		else   /* 图 */
		{
			g.arcs[g.vexnum][i].adj = 0;/* 初始化该行邻接矩阵的值(无边或弧) */
			g.arcs[i][g.vexnum].adj = 0;/* 初始化该列邻接矩阵的值(无边或弧) */
		}
		g.arcs[g.vexnum][i].info = NULL;
		g.arcs[i][g.vexnum].info = NULL;
	}
	g.vexnum++; /* 图g的顶点数加1 */
}

/* 初始条件: 图g存在,v是g中某个顶点。操作结果: 删除g中顶点v及其相关的弧 */
status deletevex(mgraph &g, vertextype v)
{
	int i, j, k;
	vrtype m = 0;
	k = locatevex(g, v); /* k为待删除顶点v的序号 */
	if (k<0)   /* v不是图g的顶点 */
		return error;
	if (g.kind == DN || g.kind == UDN)  /* 网 */
		m = infinity;
	for (j = 0; j<g.vexnum; j++)
		if (g.arcs[j][k].adj != m)   /* 有入弧或边 */
		{
			if (g.arcs[j][k].info)   /* 有相关信息 */
				delete g.arcs[j][k].info;  /* 释放相关信息 */
			g.arcnum--;    /* 修改弧数 */
		}
	if (g.kind == DG || g.kind == DN) /* 有向 */
		for (j = 0; j<g.vexnum; j++)
			if (g.arcs[k][j].adj != m) /* 有出弧 */
			{
				if (g.arcs[k][j].info)  /* 有相关信息 */
					delete g.arcs[k][j].info;  /* 释放相关信息 */
				g.arcnum--;  /* 修改弧数 */
			}
	for (j = k + 1; j<g.vexnum; j++)  /* 序号k后面的顶点向量依次前移 */
		strcpy(g.vexs[j - 1], g.vexs[j]);
	for (i = 0; i<g.vexnum; i++)
		for (j = k + 1; j<g.vexnum; j++)
			g.arcs[i][j - 1] = g.arcs[i][j];/* 移动待删除顶点之下的矩阵元素 */
	for (i = 0; i<g.vexnum; i++)
		for (j = k + 1; j<g.vexnum; j++)
			g.arcs[i - 1][i] = g.arcs[j][i]; /* 移动待删除顶点之下的矩阵元素 */
	g.vexnum--;  /* 更新图的顶点数 */
	return ok;
}

/* 初始条件: 图g存在,v和W是g中两个顶点 */
/* 操作结果: 在g中增添弧<v,w>,若g是无向的,则还增添对称弧<w,v> */
status insertarc(mgraph &g, vertextype v, vertextype w)
{
	int i, l, v1, w1;
	char *info, s[max_info];
	v1 = locatevex(g, v); //尾 
	w1 = locatevex(g, w); //头 
	if (v1<0 || w1<0)
		return error;
	g.arcnum++;  //弧或边数加1 
	if (g.kind % 2) //网 
	{
		cout << "请输入此弧或边的权值:";
		cin >> g.arcs[v1][w1].adj;
	}
	else   //图 
		g.arcs[v1][w1].adj = 1;
	cout << "是否有该弧或边的相关信息（0:无 1:有）:";
	cin >> i; cin.get();
	if (i)
	{
		cout << "请输入该弧或边的相关信息（" << max_info << "个字符）:";
		gets(s);
		l = strlen(s);
		if (l)
		{
			info = new char(l + 1);
			strcpy(info, s);
			g.arcs[v1][w1].info = info;
		}
	}
	if (g.kind>1)  /* 无向 */
	{
		g.arcs[w1][v1].adj = g.arcs[v1][w1].adj;
		g.arcs[w1][v1].info = g.arcs[v1][w1].info; /* 指向同一个相关信息 */
	}
	return ok;
}

/* 初始条件: 图g存在,v和w是g中两个顶点 */
/* 操作结果: 在g中删除弧<v,w>,若g是无向的,则还删除对称弧<w,v> */
status deletearc(mgraph &g, vertextype v, vertextype w)
{
	int v1, w1;
	v1 = locatevex(g, v); //尾
	w1 = locatevex(g, w);//头
	if (v1<0 || w1<0) /* v1、w1的值不合法 */
		return error;
	if (g.kind % 2 == 0) //图
		g.arcs[v1][w1].adj = 0;
	else //网
		g.arcs[v1][w1].adj = infinity;
	if (g.arcs[v1][w1].info) //有其他信息
	{
		delete g.arcs[v1][w1].info;
		g.arcs[v1][w1].info = NULL;
	}
	if (g.kind >= 2) /* 无向,删除对称弧<w,v> */
	{
		g.arcs[w1][v1].adj = g.arcs[v1][w1].adj;
		g.arcs[w1][v1].info = NULL;
	}
	g.arcnum--;
	return ok;
}

int visited[max_vertex_num]; /* 访问标志数组(全局量) */
status(*visitfunc)(vertextype); /* 函数变量 */

								/* 从第v个顶点出发递归地深度优先遍历图G*/
void DFS(mgraph g, int v)
{
	vertextype w1, v1;
	int w;
	visited[v] = true;  /* 设置访问标志为true(已访问) */
	visitfunc(g.vexs[v]);
	strcpy(v1, *getvex(g, v));  /* 访问第v个顶点 */
	for (w = firstadjvex(g, v1); w >= 0; w = nextadjvex(g, v1, strcpy(w1, *getvex(g, w))))
		if (!visited[w])
			DFS(g, w);/* 对v的尚未访问的序号为w的邻接顶点递归调用DFS */
}

/* 初始条件: 图g存在,visit是顶点的应用函数。 */
/* 操作结果: 从第1个顶点起,深度优先遍历图g,并对每个顶点调用函数visit */
/*一次且仅一次。一旦visit()失败,则操作失败 */
void DFStraverse(mgraph g, status(*visit)(vertextype))
{
	int v;
	visitfunc = visit;/* 使用全局变量visitfunc,使DFS不必设函数指针参数 */
	for (v = 0; v<g.vexnum; v++)
		visited[v] = false;/* 访问标志数组初始化(未被访问) */
	for (v = 0; v<g.vexnum; v++)
	{
		if (!visited[v])
			DFS(g, v);
		cout << endl;
	}
}

//单链队列
typedef vrtype qelemtype;

typedef struct  qnode
{
	qelemtype data;
	struct qnode *next;
}qnode, *queueptr;

typedef struct
{
	queueptr front; //队头指针 
	queueptr rear;  //队尾指针 
}linkqueue;
status initqueue(linkqueue &Q)
{ /* 构造一个空队列Q */
	Q.front = Q.rear = new qnode;
	if (!Q.front)
		exit(OVERFLOW);
	Q.front->next = NULL;
	return ok;
}

status destroyqueue(linkqueue &Q)
{ /* 销毁队列Q*/
	while (Q.front)
	{
		Q.rear = Q.front->next;
		delete Q.front;
		Q.front = Q.rear;
	}
	return ok;
}

status clearqueue(linkqueue &Q)
{ /* 将Q清为空队列 */
	queueptr p, q;
	Q.rear = Q.front;
	p = Q.front->next;
	Q.front->next = NULL;
	while (p)
	{
		q = p;
		p = p->next;
		delete q;
	}
	return ok;
}

status queueempty(linkqueue Q)
{ /* 若Q为空队列,则返回TRUE,否则返回FALSE */
	if (Q.front == Q.rear)
		return true;
	else
		return false;
}

int queuelength(linkqueue Q)
{ /* 求队列的长度 */
	int i = 0;
	queueptr p;
	p = Q.front;
	while (Q.rear != p)
	{
		i++;
		p = p->next;
	}
	return i;
}

status qgethead(linkqueue Q, qelemtype &e)
{ /* 若队列不空,则用e返回Q的队头元素,并返回OK,否则返回ERROR */
	queueptr p;
	if (Q.front == Q.rear)
		return error;
	p = Q.front->next;
	e = p->data;
	return ok;
}

status enqueue(linkqueue &Q, qelemtype e)
{ /* 插入元素e为Q的新的队尾元素 */
	queueptr p = new qnode;
	if (!p) /* 存储分配失败 */
		exit(OVERFLOW);
	p->data = e;
	p->next = NULL;
	Q.rear->next = p;
	Q.rear = p;
	return ok;
}

status dequeue(linkqueue &Q, qelemtype &e)
{ /* 若队列不空,删除Q的队头元素,用e返回其值,并返回OK,否则返回ERROR */
	queueptr p;
	if (Q.front == Q.rear)
		return error;
	p = Q.front->next;
	e = p->data;
	Q.front->next = p->next;
	if (Q.rear == p)
		Q.rear = Q.front;
	delete p;
	return ok;
}

/*从队头到队尾依次对队列Q中每个元素调用函数visit()。一旦visit失败,则操作失败 */
status queuetraverse(linkqueue Q, status(*visit)(qelemtype e))
{
	queueptr p;
	p = Q.front->next;
	while (p)
	{
		visit(p->data);
		p = p->next;
	}
	cout << endl;
	return ok;
}

/* 初始条件: 图g存在,visit是顶点的应用函数。*/
/* 操作结果: 从第1个顶点起,按广度优先非递归遍历图g,并对每个顶点调用函数 */
/*           visit一次且仅一次。一旦visit()失败,则操作失败。 */
/*           使用辅助队列Q和访问标志数组visited */
void BFStraverse(mgraph g, status(vertextype))
{
	int v, u, w;
	vertextype w1, u1;
	linkqueue q;
	for (v = 0; v<g.vexnum; v++)
		visited[v] = false; //置初值
	initqueue(q);  //置空的辅助队列q
	for (v = 0; v<g.vexnum; v++)
		if (!visited[v])  //v尚未访问
		{
			visited[v] = true; /* 设置访问标志为true(已访问) */
			visit(g.vexs[v]);
			enqueue(q, v); //v入队列
			while (!queueempty(q)) //队列不为空
			{
				dequeue(q, u); /* 队头元素出队并置为u */
				strcpy(u1, *getvex(g, u));
				for (w = firstadjvex(g, u1); w >= 0; w = nextadjvex(g, u1, strcpy(w1, *getvex(g, w))))
					if (!visited[w]) /* w为u的尚未访问的邻接顶点的序号 */
					{
						visited[w] = true;
						visit(g.vexs[w]);
						enqueue(q, w);
					}
			}
		}
	cout << endl;
}

/* 输出邻接矩阵g */
void display(mgraph g)
{
	int i, j;
	char s[7], s1[3];
	switch (g.kind)
	{
	case DG:strcpy(s, "有向图\0"); strcpy(s1, "弧\0"); break;
	case DN:strcpy(s, "有向网\0"); strcpy(s1, "弧\0"); break;
	case UDG:strcpy(s, "无向图\0"); strcpy(s1, "边\0"); break;
	case UDN:strcpy(s, "无向网\0"); strcpy(s1, "边\0");
	}
	cout << g.vexnum << "个顶点" << g.arcnum << "条" << s1 << "的" << s << endl;
	for (i = 0; i<g.vexnum; i++)  /* 输出g.vexs */
		cout << "g.vexs[" << i << "]=" << g.vexs[i] << endl;
	cout << "g.arcs.adj:\n"; /* 输出g.arcs.adj */
	for (i = 0; i<g.vexnum; i++)
	{
		for (j = 0; j<g.vexnum; j++)
			cout << g.arcs[i][j].adj << "\n";
	}
	cout << "g.arcs.info:\n"; /* 输出g.arcs.info */
	cout << "顶点1(弧尾) 顶点2(弧头) 该" << s1 << "信息：\n";
	if (g.kind<2) /* 有向 */
		for (i = 0; i<g.vexnum; i++)
			for (j = 0; j<g.vexnum; j++)
			{
				if (g.arcs[i][j].info)
					cout << g.vexs[i] << g.vexs[j] << g.arcs[i][j].info << endl;
			}
	else /* 无向 */
	{
		for (i = 0; i<g.vexnum; i++)
			for (j = i + 1; j<g.vexnum; j++)
				if (g.arcs[i][j].info)
					cout << g.vexs[i] << g.vexs[j] << g.arcs[i][j].info << endl;
	}
}

status print(mgraph &g)
{
	int i, j;
	cout << "输出图的顶点数组:\n";
	for (i = 0; i<g.vexnum; ++i)                      /* 输出g.vexs */
		cout << "g->vexs[" << i << "]=" << g.vexs[i] << endl;
	cout << "输出邻接矩阵：\n";
	for (i = 0; i<g.vexnum; i++)
	{
		for (j = 0; j<g.vexnum; j++)
			cout << g.arcs[i][j].adj;
		cout << endl;
	}
	return ok;
}

int main()
{

	int   k, n;
	vertextype v1, v2;

	mgraph g;
	createUDN(g);
	print(g); //输出图的顶点数组和邻接矩阵:

	printf("深度优先搜索的结果:\n");
	DFStraverse(g, visit);
	printf("广度优先搜索的结果:\n");
	BFStraverse(g, visit);
	printf("\n///////////////////////////////////////////////////////////////////\n");
	// int   k, n;
	// VertexType v1,v2;

	printf("修改顶点的值，请输入原值 新值: ");
	scanf("%s%s", v1, v2);
	putvex(g, v1, v2);
	print(g);

	printf("深度优先搜索的结果:\n");
	DFStraverse(g, visit);
	printf("广度优先搜索的结果:\n");
	BFStraverse(g, visit);

	printf("\n///////////////////////////////////////////////////////////////////\n");

	printf("插入新顶点，请输入顶点的值: ");
	scanf("%s", v1);
	insertvex(g, v1);

	printf("插入与新顶点有关的边，请输入边数: ");
	scanf("%d", &n);
	for (k = 0; k<n; k++)
	{
		printf("请输入另一顶点的值: ");
		scanf("%s", v2);
		insertarc(g, v1, v2);
	}
	print(g);

	printf("深度优先搜索的结果:\n");
	DFStraverse(g, visit);
	printf("广度优先搜索的结果:\n");
	BFStraverse(g, visit);
	printf("\n///////////////////////////////////////////////////////////////////\n");


	printf("删除顶点及相关的边，请输入顶点的值: ");
	scanf("%s", v1);
	deletevex(g, v1);

	print(g);

	printf("深度优先搜索的结果:\n");
	DFStraverse(g, visit);
	printf("广度优先搜索的结果:\n");
	BFStraverse(g, visit);
	printf("\n///////////////////////////////////////////////////////////////////\n");
	destroygraph(g);

}

void main()
{

	int   k, n;
	VertexType v1, v2;

	MGraph g;
	CreateAN(&g);
	Print(&g); //输出图的顶点数组和邻接矩阵:

	printf("深度优先搜索的结果:\n");
	DFSTraverse(g, visit);
	printf("广度优先搜索的结果:\n");
	BFSTraverse(g, visit);
	printf("\n///////////////////////////////////////////////////////////////////\n");
	// int   k, n;
	// VertexType v1,v2;

	printf("修改顶点的值，请输入原值 新值: ");
	scanf("%s%s", v1, v2);
	PutVex(&g, v1, v2);
	Print(&g);

	printf("深度优先搜索的结果:\n");
	DFSTraverse(g, visit);
	printf("广度优先搜索的结果:\n");
	BFSTraverse(g, visit);

	printf("\n///////////////////////////////////////////////////////////////////\n");

	printf("插入新顶点，请输入顶点的值: ");
	scanf("%s", v1);
	InsertVex(&g, v1);

	printf("插入与新顶点有关的边，请输入边数: ");
	scanf("%d", &n);
	for (k = 0; k<n; k++)
	{
		printf("请输入另一顶点的值: ");
		scanf("%s", v2);
		InsertArc(&g, v1, v2);
	}
	Print(&g);

	printf("深度优先搜索的结果:\n");
	DFSTraverse(g, visit);
	printf("广度优先搜索的结果:\n");
	BFSTraverse(g, visit);
	printf("\n///////////////////////////////////////////////////////////////////\n");


	printf("删除顶点及相关的边，请输入顶点的值: ");
	scanf("%s", v1);
	DeleteVex(&g, v1);

	Print(&g);

	printf("深度优先搜索的结果:\n");
	DFSTraverse(g, visit);
	printf("广度优先搜索的结果:\n");
	BFSTraverse(g, visit);
	printf("\n///////////////////////////////////////////////////////////////////\n");
	DestroyGraph(&g);

}