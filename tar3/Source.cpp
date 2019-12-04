#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <functional>
#include"BTree.h"
#include"Lending.h"

using namespace std;


int main()
{

	char ch;
	BTree<Lending> bt;
	vector<string> ids;
	Lending l1, l2;
	//int id;
	string str, str1, str2;
	vector<Lending> keys;
	//Lending *p;

	cout << "\nChoose one of the following" << endl;
	cout << "1: add a new lending" << endl;
	cout << "2: return an item" << endl;
	cout << "3: print all lendings " << endl;
	cout << "4: print all lendings of a date " << endl;
	cout << "5: exit:" << endl;
	do
	{
		cin >> ch;

		switch (ch)
		{
		case '1':
			cout << "Enter lending data\n";
			cin >> l1;
			bt.insert(l1);
			break;

		case '2':
			cout << "Enter lending data\n";
			cin >> l1;
			bt.deleteVal(l1);
			break;
		case '3':
			bt.printTree();
			break;
		case '4':cout << "Enter the required date\n";
			cin >> str;
			str1 = str.substr(0, str.length() - 1); //before date
			str2 = str + '*'; //after date
			l1.set_date(str1);
			l2.set_date(str2);
			//bt.printBetween(l1, l2);
			//bt.printAllKeys()
			cout << "dont know whats going on?" << endl;
			break;
		case '5':cout << "bye "; break;
		default: cout << "error ";  break;
		}//switch
	} while (ch != '5');
	return 0;
}