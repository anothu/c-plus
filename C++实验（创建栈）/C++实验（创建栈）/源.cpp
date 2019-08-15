#include <iostream>
#include"stack.h";
using namespace std;
int main()
{
	Istack<char> sta;
	int choice;
	menu();
	while (true)
	{
		cout << "请输入你的选择:";
		cin >> choice;
		switch (choice)
		{
		case 1:
			char n;
			cout << "请输入要入栈的元素:" << endl;
			cin >> n;
			sta.Push(n);
			break;
		case 2:
			sta.Pop();
			break;
		case 3:
			if (sta.Empty())
				cout << "此时栈为空!" << endl;
			else
				cout << "栈顶元素为:" << sta.GetTop();
			break;
		case 4:
			if (sta.Empty())
				cout << "此时栈为空!" << endl;
			else
				cout << "栈不为空!" << endl;
			break;
		case 5:
			cout << "栈中元素个数为:" << sta.Size() << endl;
			break;
		case 6:
			sta.ClearStack();
			cout << "栈已清空" << endl;
			break;
		}
	}
}
