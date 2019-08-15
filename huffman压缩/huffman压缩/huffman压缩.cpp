// Main.cpp: 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include"Compress.h"
#include"Huffman.h"
#include<iomanip>
#include<iostream>
using namespace std;
//#pragma warning(disable:4996)

int main()
{
	char filename[256];
	cout << "========哈夫曼文件压缩=========" << endl;
	cout << "输入文件路径:";
	cin >> filename;



	Compress(filename);
	system("pause");
	//getchar();
	return 0;
}
