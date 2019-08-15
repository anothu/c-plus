#pragma once
#define OK 0;
#define ERROR 1;
struct HTNode
{
	int nWeight;//权值
	int nParent;//父节点
	int nLchild;//左子
	int nRchild;//右子
};

typedef HTNode *HuffmanTree;
					 
typedef char **HuffmanCode;

int HuffmanTreeing(HuffmanTree &pHT, int *w, int n);
int HuffmanCoding(HuffmanCode &pHC, HuffmanTree &pHT);
int Selcet(HuffmanTree pHT, int nSize);



