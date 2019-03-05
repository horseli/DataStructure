#include<iostream>
#include<string>
using namespace std;
#define TRUE 1;
#define FALSE 0;
int n = 0;
struct Node {
	char date;
	Node*lchild;
	Node*rchild;
};
template<typename E>class Queue {
	int maxSize;
	int font;
	int rear;
	E*list;
public:
	Queue(int size = 10)
	{
		maxSize = size + 1;
		font = 1;
		rear = 0;
		list = new E[maxSize];
	}
	void EnQueue(E s)
	{
		if ((rear - font + maxSize + 2) % maxSize >= maxSize)//栈满
		{
			list = (E*)malloc(maxSize + 1);
			maxSize++;
		}
		list[(rear + 1) % maxSize] = s;
		rear = (rear + 1) % maxSize;
	}
	E DeQueue()
	{
		if (rear - font == -1)
		{
			cout << "栈空";

		}
		E temp = list[font];
		font = (font + 1) % maxSize;
		return temp;
	}
	void clear()
	{
		font = 1;
		rear = 0;
	}
	int isEmpty()
	{
		if (rear - font == -1)
			return TRUE;

		return FALSE;
	}
};
class BinTree {
public:
	string s;
	int len;
	Node*root;
	Queue<Node>q;
	Node*newNode(char s)
	{
		Node*p = new Node;
		p->date = s;
		p->lchild = NULL;
		p->rchild = NULL;
		return p;
	}
	BinTree(string a)
	{
		s = a;
		len = s.length();

	}
	void intialize(Node**root)//函数传参是单向值传递，所以想改变指针的值的话，则必须传递二重指针才行。
	{
		//Node*b = root;

		if (n < len&&s[n] <= 'z'&&s[n] >= 'a') {
			*root = new Node;
			(*root)->lchild = NULL;
			(*root)->rchild = NULL;
			(*root)->date = s[n];
			//cout << (*root)->date << "#";
			n++;
			intialize(&(*root)->lchild);
			intialize(&(*root)->rchild);
		}
		else
		{
			*root = new Node;
			(*root)->lchild = NULL;
			(*root)->rchild = NULL;
			(*root)->date = s[n];
			//cout << (*root)->date << "#";
			n++;
		}
	}
	//void insert()
	void preorder(Node*root)
	{
		if (root)
		{
			//cout << "d";


			cout << root->date << " ";
			preorder(root->lchild);
			preorder(root->rchild);
		}
	}
	void inorder(Node*root)
	{
		if (root)
		{


			inorder(root->lchild);

			cout << root->date << " ";
			inorder(root->rchild);
		}
	}
	void level(Node*root)
	{

		Node p = q.DeQueue();
		cout << p.date;
		while (root->lchild)
			q.EnQueue(*(root->lchild));
		while (root->rchild)
			q.EnQueue(*(root->rchild));
	}
	void levelTravel(string &s)
	{

		int i = 0;
		q.EnQueue(*root);
		while (q.isEmpty() == 0 && i<s.length())
		{
			//cout << q.isEmpty();
			Node p = q.DeQueue();
			s[i] = p.date;
			if (p.lchild)
				q.EnQueue(*(p.lchild));
			if (p.rchild)
				q.EnQueue(*(p.rchild));
			i++;
		}

	}
};
void f(string &s)
{
	s[0] = 's';
	cout << s << endl;
}
int main()
{
	int nn;
	cin >> nn;
	string *a, *b;
	//string m;
	a = new string[nn];
	b = new string[nn];
	/*for (int i = 0; i < n; i++)
	{
	cin >> a[i];
	b[i] = a[i];
	}
	for (int i = 0; i < n; i++)
	{
	cout << b[i];
	}*/
	/*cin>>a[0];
	f(a[0]);
	cout << a[0];*/
	for (int i = 0; i < nn; i++)
	{
		string m;
		cin >> a[i];
		BinTree T = BinTree(a[i]);
		n = 0;
		T.intialize(&T.root);
		/*T.preorder(T.root);
		cout << endl;
		T.inorder(T.root);
		cout << endl;*/

		T.levelTravel(a[i]);
		b[i] = m;

	}
	for (int i = 0; i < nn; i++)
	{
		cout << a[i] << endl;
	}
	system("pause");
}
