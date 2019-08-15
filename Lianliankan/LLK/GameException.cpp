#include "stdafx.h"
#include "GameException.h"


CGameException::CGameException(LPCTSTR text)
{
	int answer = MessageBox(NULL, text, _T("´íÎó"), MB_ICONSTOP | MB_OK);
	if (answer == IDOK)
		exit(0);
}


CGameException::~CGameException()
{
}
