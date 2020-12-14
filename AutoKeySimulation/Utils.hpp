/*
	12/13/2020
	Utils.hpp
	Made by tostring
*/

#pragma once

#include <Windows.h>
#include <string>
#include <iostream>
#include <vector>
#include <WinUser.h>
#include <conio.h>

namespace std
{
	template<class _container,
		class _Ty> inline
		bool contains(_container _C, const _Ty& _Val)
	{
		return std::find(_C.begin(), _C.end(), _Val) != _C.end();
	}
};

using namespace std;

string classnametolookfor;
vector<HWND> hwndlist;

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	char class_name[256];
	GetClassName(hwnd, class_name, sizeof(class_name));

	if (class_name == classnametolookfor && IsWindow(hwnd) && !contains(hwndlist, hwnd)) {
		hwndlist.push_back(hwnd);
		return TRUE;
	}

	return TRUE;
}

void TypeInWindow(HWND window, string msg) {
	for (size_t i = 0; i < msg.length(); i++)
	{
		PostMessage(window, WM_CHAR, msg[i], 0);
	}
}

void TypeInWindow(HWND window, char msg) {
	PostMessage(window, WM_CHAR, msg, 0);
}

void TypeInWindow(HWND window, string msg, int sleeptime) {
	for (size_t i = 0; i < msg.length(); i++)
	{
		PostMessage(window, WM_CHAR, msg[i], 0);
		Sleep(sleeptime);
	}
}

bool WindowExists(string windowname) {
	return FindWindow((LPCSTR)windowname.c_str(), NULL);
}

vector<HWND> AddWindowsWithClassNameToList(string classname, vector<HWND> list) {
	hwndlist = list;
	classnametolookfor = classname;
	EnumWindows(EnumWindowsProc, NULL);
	return hwndlist;
}