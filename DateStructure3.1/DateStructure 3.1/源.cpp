#include<iostream>
#include<string>
using namespace std;
#define TRUE 1;
#define FALSE 0;

struct Node {
	char date;
	Node*lchild;
	Node*rchild;
};
class BinTree {
public:
	string s;
	int len;
	Node*root;
	int n = 0;
	int level;
	Node*newNode(char s)
	{
		Node*p = new Node;
		p->date = s;
		p->lchild = NULL;
		p->rchild = NULL;
		return p;
	}
	BinTree() {};
	BinTree(string a)
	{
		s = a;
		len = s.length();

	}
	void create(string a) {
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
	
	//void height(Node*root,int h=0)
	//{
	//	if (!root)
	//		return;
	//	//cout << h << "(";
	//	if (h > level)
	//		level = h;
	//	if (root->lchild)
	//		height(root->lchild, h+1);
	//	if (root->rchild)
	//		height(root->rchild, h+1);
	//	
	//}
	void height1(Node*root, int&level,int h = 0)
	{
		if (!root)
			return;
		//cout << h << "(";
		if (h > level)
			level = h;
		if (root->lchild)
			height1(root->lchild,level, h + 1);
		if (root->rchild)
			height1(root->rchild, level,h + 1);

	}
	bool isBanlanced(Node*root);
};
bool BinTree::isBanlanced(Node*root)
{
	if (root==NULL)
		return TRUE;
	Node*rootl = root->lchild;
	Node*rootr = root->rchild;
	int h1 = 0;
	int h2 = 0;
	height1(rootl, h1);
	height1(rootr, h2);
	//cout << h1 << h2 << endl;
	if (h1 - h2 <= 1 && h1 - h2 >= -1)
		return TRUE;
	return FALSE;
}
int main()
{
	int n;
	cin >> n;
	BinTree*T = new BinTree[n];
	string s;
	cin >> s;
	for (int i = 0; i < n; i++)
	{
		getline(cin, s);
		T[i].create(s);
		T[i].intialize(&T[i].root);

	}
	for (int i = 0; i < n; i++)
	{
		cout << T[i].isBanlanced(T[i].root) << endl;
	}
	string s1 = "qxABzCgRQ";
	string s2 = "rAB";
	string s3 = "bCdEfGH ";
	string s4 = "abmqPDWSE";
	/*int a = 0;
	int b = a++;
	cout << b<<"t";*/
//	BinTree T1(s1);
//	T1.intialize(&T1.root);
//	//T1.inorder(T1.root);
//	//int h = 0;
//	//T1.height(T1.root, h);
//	//cout << h << "%";
//	cout << T1.isBanlanced(T1.root)<< "*";
//	/*int h = 0;
//	T1.height(T1.root, h);
//	h = 0;
//	T1.height1(T1.root, h);
//	cout << h << "%";*/
//	BinTree T2(s2);
//	T2.intialize(&T2.root);
//	cout << T2.isBanlanced(T2.root) << "*";
//	/*h = 0;
//	T2.height(T2.root, h);
//	h = 0;
//	T2.height1(T2.root, h);
//	cout << h << "%";*/
//	BinTree T3(s3);
//	
//	T3.intialize(&T3.root);
//	
//	cout << T3.isBanlanced(T3.root) << "*";
////h = 0;
////	T3.height(T3.root, h);
////	cout << T3.level << "%";
//	BinTree T4(s4);
//	T4.intialize(&T4.root);
//	//T4.inorder(T4.root);
//	/*int h = 0;
//	T4.height(T4.root, h);
//	cout << h << "%";
//	cout << T4.root->date << ":";*/
//	cout << T4.isBanlanced(T4.root) << "*";
//	/*h = 0;
//	T4.height(T4.root, h);
//	cout << T4.level << "%";*/
	system("pause");
}