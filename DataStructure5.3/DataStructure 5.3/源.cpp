#include<iostream>
#include<string>
#include <sstream>
# include <stdlib.h>
using namespace std;
struct hashdict
{
	string str;
	int times;
};
void output() {
	int n;
	cin >> n;
	hashdict*hash = new hashdict[n];
	for (int i = 0; i < n; i++) {
		hash[i].times = -1;
	}
	int num;
	cin >> num;
	/*char ch;
	cin.get(ch);*/
	string s;
	/*hash function*/
	for (int k = 0; k < n;k++) {
		cin >> s;
		int lenth = s.length();
		int sum = 0;
		for (int i = 0; i < lenth; i++) {
			sum += int(s[i]);
		}
		int mood = sum%n;
		for (int i = mood; i < mood + n; i++)
		{
			int is = i%n;
			if (hash[i].str == s) {
				hash[i].times++;
				break;
			}
			if (hash[is].times == -1) {
				hash[is].str = s ;
				hash[is].times = 1;
				break;
			}
		}
	}
	/*find*/
	string ret;
	stringstream ss;
	for (int i = 0; i < num; i++) {
		cin >> s;
		int lenth = s.length();
		int sum = 0;
		for (int i = 0; i < lenth; i++) {
			sum += int(s[i]);
		}
		int mood = sum%n;
		int k = 0;
		for (int i = mood; i < mood + n; i++) {
			int is = i%n;
			if (hash[is].str == s) {
				
				//ss<<hash[is].times;
			    //ss >> ret;
				char m[3];
				//itoa(hash[is].times, m,3);
				//ret +=std::to_string(hash[is].times)+ " ";
				cout << hash[is].times << " ";
				k = 1;
				break;
			}
		}
		if (k == 0) {
			//1ret+="0 ";
			cout << "0 ";
		}
	}
	//ss >> ret;
	//cout << ret << endl;
	//return ret;
}
int main() {
	/*stringstream ss;
	ss << 5;
	string s;
	ss >> s;
	cout << s;
	s=to_string(4)+" "+to_string(5);
	cout << s;*/
	int n;
	cin >> n;
	string *st = new string[n];
	for (int i = 0; i < n; i++) {
		output();
		cout << endl;
	}
	/*for (int i = 0; i < n; i++) {
		cout << st[i] << endl;
	}
	*/
	//system("pause");
}
