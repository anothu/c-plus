#include "stdafx.h"
#include"Huffman.h"
#include<iostream>

using namespace std;
#define MAX 0x7FFFFFFF
#pragma warning(disable:4996)



int HuffmanTreeing(HuffmanTree &pHT, int *w, int n)
{
	pHT = (HuffmanTree)malloc((2 * n) * sizeof(HTNode));
	for (int i = 1; i <= n; i++)
	{
		pHT[i].nWeight = w[i - 1];
		pHT[i].nLchild = 0;
		pHT[i].nRchild = 0;
		pHT[i].nParent = 0;
	}
	for (int i = n + 1; i <= 2 * n - 1; i++)
	{
		pHT[i].nParent = 0;
		pHT[i].nLchild = 0;
		pHT[i].nRchild = 0;
		pHT[i].nWeight = 0;
	}
	for (int k = n + 1; k < 2 * n; k++)
	{
		int i1, i2;
		i1 = Selcet(pHT, k - 1);
		pHT[i1].nParent = k;
		i2 = Selcet(pHT, k - 1);
		pHT[i2].nParent = k;
		pHT[k].nLchild = i1;
		pHT[k].nRchild = i2;
		pHT[k].nWeight = pHT[i1].nWeight + pHT[i2].nWeight;
	}
	return 0;
}
int Selcet(HuffmanTree pHT, int nSize)
{
	int minValue = MAX;//最小值
	int min = 0;//元素符号
	for (int i = 0; i <= nSize; i++)
	{
		if (pHT[i].nParent == 0 && pHT[i].nWeight < minValue)
		{
			minValue = pHT[i].nWeight;
			min = i;
		}
	}
	return min;
}
int HuffmanCoding(HuffmanCode &pHC, HuffmanTree &pHT)
{
	//非递归先序遍历
	char cd[256] = { '\0' };
	int cdlen = 0;
	for (int i = 1; i < 512; i++)
	{
		pHT[i].nWeight = 0;
	}
	int p = 511;
	while (p != 0)
	{
		if (pHT[p].nWeight == 0)//左子
		{
			pHT[p].nWeight = 1;
			if (pHT[p].nLchild != 0)
			{
				p = pHT[p].nLchild;
				cd[cdlen++] = '0';
			}
			else if (pHT[p].nRchild == 0)
			{
				pHC[p] = (char*)malloc((cdlen + 1) * sizeof(char));
				cd[cdlen] = '\0';
				strcpy(pHC[p], cd);
			}
		}
		else if (pHT[p].nWeight == 1)//右子
		{
			pHT[p].nWeight = 2;
			if (pHT[p].nRchild != 0)
			{
				p = pHT[p].nRchild;
				cd[cdlen++] = '1';
			}
		}
		else
		{
			pHT[p].nWeight = 0;
			p = pHT[p].nParent;
			cdlen--;
		}
	}
	return OK;
}


