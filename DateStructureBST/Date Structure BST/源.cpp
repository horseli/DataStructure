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
	
	
	int num = 0;
	int size;
public:
	Node*root;
	int le=0;
	int *a;
	BTree(int*b,int n) {
		a = new int[n];
		for (int i = 0; i < n; i++)
		{
			a[i] = b[i];
		}
		size = n;
	}
	void buildBST(Node**r) {
		if(num!=0)num++;
		(*r) = new Node;
		(*r)->l = NULL;
		(*r)->r = NULL;
		(*r)->date = a[num];
		
		if (num == size - 1)
			return;
		if (a[num] < a[num + 1])
		{
			buildBST(&((*r)->r));
			//num++;
		}
		if (a[num] > a[num + 1])
		{
			buildBST(&((*r)->l));
			//num++;
		}
	}
	void inorder(Node*root) {
		if (root)return;
		inorder(root->l);
		cout << root->date << " ";
		inorder(root->r);
	}
	void height(Node*r,int level)
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

int main()
{
	
	int m[9] = {37,24,42,32,7,40,2,42,120};
	int n[9] = { 120,42,7,2,32,42,24,37,40 };
	/*for (int i = 0; i < 9; i++)
	{
		cin >> m[i];
	}*/
	BTree T(m,9);
	cout << T.a[0]<< T.a[1]<< T.a[2]<< T.a[3];
	T.buildBST(&T.root);
	T.inorder(T.root);
	cout <<"I"<< endl;
	T.height(T.root, 1);
	cout << T.le << endl;
	BTree T2(n, 9);
	T2.buildBST(&T.root);
	T2.height(T.root, 1);
	cout << T2.le << endl;
	system("pause");
}