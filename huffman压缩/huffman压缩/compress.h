#pragma once
#include"Compress.h"
#include"Huffman.h"

struct HEAD
{
	char type[4];
	int length;
	int weight[256];
};
typedef char* BUFFER;


int InitHead(const char *pFilename, HEAD &sHead);
int Compress(const char *pFilename);
int Encode(const char *pFilename, const HuffmanCode pHC, BUFFER &pBuffer, const int nSize);
char Str2byte(const char *pBinStr);
int WriteFile(const char *pFilename, const HEAD sHead, const BUFFER pBuffer, const int nSize);


