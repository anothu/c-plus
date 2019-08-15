#include "stdafx.h"
#include"Compress.h"
#include<iostream>
#include <stdlib.h>
#include"Huffman.h"
using namespace std;


char Str2byte(const char *pBinStr)//String to Byte
{
	char b = 0x00;
	for (int i = 0; i < 8; i++)
	{
		b = b << 1;
		if (pBinStr[i] == '1')
		{
			b = b | 0x01;
		}
	}
	return b;
}

int Encode(const char *pFilename, const HuffmanCode pHC, BUFFER &pBuffer, const int nSize)
{
	//打开文件
	FILE *in = fopen(pFilename, "rb");
	pBuffer = (char *)malloc(nSize * sizeof(char));
	if (!pBuffer)
	{
		cout << "开辟缓冲区失败" << endl;
	}

	char cd[256] = { 0 };		//工作区
	int pos = 0;				//缓冲区指针
	int ch;
	//扫描文件
	while ((ch = fgetc(in)) != EOF)
	{
		strcat(cd, pHC[ch + 1]);

		//压缩编码
		while (strlen(cd) >= 8)
		{
			pBuffer[pos++] = Str2byte(cd);
			for (int i = 0; i < 256 - 8; i++)
			{
				cd[i] = cd[i + 8];
			}
		}
	}
	if (strlen(cd) > 0)
	{
		pBuffer[pos++] = Str2byte(cd);
	}
	fclose(in);		//关闭文件

	return OK;
}

int InitHead(const char *pFilename, HEAD &sHead)
{
	strcpy(sHead.type, "HUF");		//文件类型
	sHead.length = 0;				//源文件长度
	for (int i = 0; i < 256; i++)
	{
		sHead.weight[i] = 0;		//权值
	}

	//以二进制流形式打开文件
	FILE *in = fopen(pFilename, "rb");
	//扫描文件，获得权重
	int ch;
	while ((ch = fgetc(in)) != EOF)
	{
		sHead.weight[ch]++;
		sHead.length++;
	}
	fclose(in);
	in = NULL;
	return OK;
}
int Compress(const char *pFilename)
{
	int weight[256] = { 0 };
	FILE *in = fopen(pFilename, "rb");
	int ch;
	while ((ch = getc(in)) != EOF)
	{
		weight[ch]++;
	}
	fclose(in);
	HuffmanTree pHT = new HTNode[512];
	char** pHC = new char*[257];
	HuffmanTreeing(pHT, weight, 256);
	HuffmanCoding(pHC, pHT);

	int nSize = 0;
	for (int i = 0; i < 256; i++)
		nSize += weight[i] * strlen(pHC[i + 1]);
	nSize = (nSize % 8) ? nSize / 8 + 1 : nSize / 8;


	char *pBuffer = NULL;
	pBuffer = new char[nSize];
	memset(pBuffer, 0, (nSize) * sizeof(char));
	Encode(pFilename, pHC, pBuffer, nSize);
	if (!pBuffer) {
		return ERROR;
	}

	HEAD sHead;
	InitHead(pFilename, sHead);
	cout<<"before:" << sHead.length << "字节" << endl;
	int afterlen = WriteFile(pFilename, sHead, pBuffer, nSize);
	cout<<"after: " << afterlen << "字节" << endl;
	cout << "压缩比率：" << (double)afterlen * 100 / sHead.length << "%" << endl;

	delete pHT; delete[] pHC; delete pBuffer;

	return OK;
}

int WriteFile(const char *pFilename, const HEAD sHead, const BUFFER pBuffer, const int nSize)
{
	//生成文件名
	char filename[256] = { 0 };
	strcpy(filename, pFilename);
	strcat(filename, ".huf");

	//以二进制流形式打开文件
	FILE * out = fopen(filename, "wb");

	//写文件
	fwrite(&sHead, sizeof(HEAD), 1, out);

	//写压缩后的编码
	fwrite(pBuffer, sizeof(char), nSize, out);
	//关闭文件，释放文件指针
	fclose(out);
	out = NULL;

	cout << "生成压缩文件：" << filename << endl;
	int len = sizeof(HEAD) + strlen(pFilename) + 1 + nSize;
	return len;
}
