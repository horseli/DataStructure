#include<iostream>
#include<string>
using namespace std;
int main()
{
	int n;
	cin >> n;
	int*p = new int[n];
	for (int i = 0; i < n; i++) {
		p[i] = -1;
	}
	char s;
	int sm;
	int mood;
	int num;
	//cout << s;
	//getline(cin, s);
	int j = 0;
	//int lent = s.length();
	cin.get(s);
	while (cin>>num) {
		sm = num ;
		//cout << sm;
		mood = sm%n;
		for (int i = mood; i < mood + n; i++) {
			int nn = i%n;
			if (p[nn]==-1) {
				p[nn] = sm;
				//cout << nn << " " << sm << endl;
				break;
			}
		}
		j += 1;
		cin.get(s);
		if (s == '\n')
			break;
	}
	for (int i = 0; i < n; i++) {
		if(p[i]!=-1)
		cout << i << " "<<p[i] << endl;
	}
	system("pause");
}