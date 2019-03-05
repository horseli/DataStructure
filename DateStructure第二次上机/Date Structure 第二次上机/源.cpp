#include<iostream>
using namespace std;
struct Node
{
	int date;
	Node*l;
	Node*r;
};
class BTree
{


	int num = -1;
	int size;
public:
	Node*root;
	int le = 0;
	int *a;
	BTree(int*b, int n) {
		a = new int[n];
		for (int i = 0; i < n; i++)
		{
			a[i] = b[i];
		}
		size = n;
	}
	void buildBST(Node*&root) {
		/*if (num != 0)
		{
			num++;
			(*r) = new Node;
			(*r)->l = NULL;
			(*r)->r = NULL;
			(*r)->date = a[num];
		}
		if (num == 0) {
			(*r) = new Node;
			(*r)->l = NULL;
			(*r)->r = NULL;
			(*r)->date = a[num];
			num++;
		}*/
		num++;
		root = new Node;
		root->l = root->r = NULL;
		root->date=a[0];
		Node*r = root;
		Node*pre = NULL;
		int temp = 0;
		//cout << "()*&(*&(";
		for (int i = 1; i < 9; i++)
		{
			while (r) {
				pre = r;
				if ((r) && a[i] >=(r)->date)
				{
					if ((r) == NULL)
						break;
					r = (r)->r;
					temp = 1;
				}
				else if ((r) && a[i] < (r)->date) {
					if ((r) == NULL)
						break;
					r = (r)->l;
					temp = 0;
				}
			}
			r = new Node;
			(r)->l = (r)->r = NULL;
			(r)->date = a[i];
			if (temp)
				pre->r = r;
			else pre->l = r;
			r=root;
			cout << i;
		}
		//cout << "()*&(*&(";
		cout << root->date << "*";
		cout << root->l->date<<"*";
		cout << root->l->l->date << "*";
		/*for (int i = 0; i < size; i++)
		{
			while (*root) {
				while ((*root) && a[i] > (*root)->date)
				{
					if ((*root)==NULL)
						break;
					*root = (*root)->r;
				}
				while ((*root)&&a[i] < (*root)->date) {
					if ((*root)==NULL)
						break;
					*root = (*root)->l;
				}
			}
			*root = new Node;
			(*root)->l = (*root)->r = NULL;
			(*root)->date = a[i];
			root = r;
		}*/
		//if (num > size - 1)
		//	return;
		//(*r) = new Node;
		//(*r)->l = NULL;
		//(*r)->r = NULL;
		//(*r)->date = a[num];
		//

		//
		//if (a[num] < a[num + 1])
		//{
		//	buildBST(&((*r)->r));
		//	//num++;
		//}
		//if (a[num] > a[num + 1])
		//{
		//	buildBST(&((*r)->l));
		//	//num++;
		//}
	}
	void compare(Node**root, int a) {
		while (*root) {
			while (a > (*root)->date)
				*root = (*root)->r;
			while (a < (*root)->date)
				*root = (*root)->l;
		}
		*root = new Node;
		(*root)->l = (*root)->r = NULL;
		(*root)->date = a;
	}
	void inorder(Node*root) {
		if (root==NULL)return;
		inorder(root->l);
		cout << root->date << " ";
		inorder(root->r);
	}
	void height(Node*r, int level)
	{
		if (r == NULL)
			return;
		if (level > le)
			le = level;
		if (r->l)
			height(r->l, level + 1);
		if (r->r)
			height(r->r, level + 1);
	}
};
//BTree BTree(Node**root)
//{
//
//}
void f(int*a)
{
	a = new int[2];
	a[0] = 1;
	a[1] = 0;
}
int main()
{

	int m[9] = { 37,24,42,32,7,40,2,42,120 };
	int n[9] = { 120,42,7,2,32,42,24,37,40 };
	/*for (int i = 0; i < 9; i++)
	{
	cin >> m[i];
	}*/
	BTree T(m, 9);
	//cout << T.a[0] << T.a[1] << T.a[2] << T.a[3];
	T.buildBST(T.root);
	T.inorder(T.root);
	cout << "I" << endl;
	T.height(T.root, 1);
	cout << T.le << endl;
	BTree T2(n, 9);
	T2.buildBST(T.root);
	T2.height(T.root, 1);
	cout <<"e"<< T2.le << endl;
	/*int s[2] = { 1,2 };
	int *s1;
	f(s1);
	cout << s1[1];*/
	system("pause");
}