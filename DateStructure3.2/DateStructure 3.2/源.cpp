#include<iostream>
#include<string>
using namespace std;
#define TRUE 1;
#define FALSE 0;

struct Node {
	char date;
	int weight;
	Node*lchild;
	Node*rchild;
};
struct List
{
	Node*dat;
	List*next;
};
class BinTree {
public:
	string sdate;
	int len;
	int lenDate;
	Node*root;
	Node*num;
	List*list;
	int*codeNum;
	int n = 0;
	int level;
	Node*newNode(int w, char s='!')
	{
		Node*p = new Node;
		p->date = s;
		p->weight = w;
		p->lchild = NULL;
		p->rchild = NULL;
		return p;
	}
	BinTree(){}
	BinTree(int n) {
		
		len = n;
		num = new Node[len];
		for (int i = 0; i < n; i++)
		{
			cin >> num[i].date;
			cin >> num[i].weight;
		}
		/*for (int i = 0; i < n; i++) {
			cout << num[i].weight << " ";
		}*/
	}
	/*BinTree(int w,char a='!')
	{
		root->date = a;
		root->weight = w;

	}*/
	void create(char a, int w) {
		root->date = a;
		root->weight = w;
	}
	void intialize(Node*&root);//函数传参是单向值传递，所以想改变指针的值的话，则必须传递二重指针才行。
	void buildHuff();
	int find(char ch) {
		for (int i = 0; i < len; i++)
		{
			if (num[i].date == ch) {
				return num[i].weight;
			}
		}
		exit(0);
	}
	void insert(List*p) {
		List*q = list;
		List*s = list;
		/*first*/
		if (q->dat->weight > p->dat->weight) {
			p->next = q;
			list = p;
			return;
		}
		q = q->next;
		//int i = 0;
		while (q!=NULL) {
			/*last*/
			
			if (p->dat->weight < q->dat->weight) {
				s->next = p;
				p->next = q;
				return;
			}
			
			s = q;
			q = q->next;
			//i++;
			if (q == NULL)
				cout << ";";
		}
		
			s->next = p;
			return;
		
	}
	int output();
	void preorder(Node*root)
	{
		if (root)
		{
			//cout << root->date << " ";
			if(root->lchild==NULL&&root->rchild == NULL){
			codeNum[n] = 0;
			height(root, codeNum[n]);
			
			cout << codeNum[n] << " ";
			n++;}
			//cout << root->weight;5
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
	void height(Node*root, int&level, int h = 0)
	{
		if (!root)
			return;
		//cout << h << "(";
		if (h > level)
			level = h;
		if (root->lchild)
			height(root->lchild, level, h + 1);
		if (root->rchild)
			height(root->rchild, level, h + 1);
		else { codeNum[n] = h; 
		n++;
		}

	}

};

void BinTree::intialize(Node*&root) {
	cin >> sdate;
	lenDate = sdate.length();
	codeNum = new int[lenDate];
	list = new List;
	list->dat = new Node;
	list->dat->date=sdate[0];
	list->dat->weight = find(list->dat->date);
	list->dat->lchild = NULL;
	list->dat->rchild = NULL;
	List*p;
	List*q = list;
	for (int i = 1; i < lenDate; i++) {
		p = new List;
		p->dat = new Node;
		p->dat->date = sdate[i];
		p->dat->weight = find(p->dat->date);
		p->dat->lchild = NULL;
		p->dat->rchild = NULL;
		q->next = p;
		q = p;
	}

	q->next = NULL;
	/*q->next->dat = new Node;
	q->next->dat->weight=0;*/
	
	/*try travel*/
	/*p = list;
	cout << p->dat->date;
	while (p)
	{
		cout << p->dat->date << p->dat->weight << " ";
		p = p->next;
	}*/
}
void BinTree::buildHuff() {
	Node*sl, *sr, *sp=NULL;
	while (list) {
		/*find two min for Huff*/
		sl = list->dat;
		sr=list->next->dat;
		sp = newNode(list->dat->weight + list->next->dat->weight);
		sp->lchild = sl;
		sp->rchild = sr;
		if (list->next->next == NULL)
			break;
		list = list->next->next;
		/*intial splist to insert*/
		List*splist = new List;
		splist->dat = sp;
		splist->next = NULL;
		insert(splist);
	}
	root = sp;
}
int BinTree::output(){
	//preorder(root);
	int total=0;
	for (int i = 0; i < lenDate; i++)
		total += codeNum[i];
	return total;
}
int main()
{
	int n;
	cin >> n;
	BinTree T(n);
	T.intialize(T.root);
	
	T.buildHuff();
	int level = 0;
	T.height(T.root, level);
	cout << level << "N";
	cout << T.output() << endl;
	
	/*string s = "1234";
	s[2] = ' ';
	cout << s << endl;
	for (int i = 0; i < s.length(); i++)
	{
		if(s[i]!=' ')
		cout << s[i];
	}
	*/
	system("pause");
}