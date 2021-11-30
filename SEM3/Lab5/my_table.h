#pragma once
#include "resource2.h"
#include "framework.h"
#include <string>
#include <fstream>

extern int CurListSel;

class MyTable
{
public:
	HWND tableHwnd = NULL;
	void Add(std::string str);
	void ClearTableFile();
	void CreateTable(HINSTANCE hInst, HWND hWnd);
};