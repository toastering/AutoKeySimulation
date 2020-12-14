#include "Utils.hpp"

#define TriggerBind 'A'
#define TypeMsg "gay"
#define WindowName "Valve001"

vector<HWND> windows;

DWORD WINAPI ListenHandler(__in LPVOID lpParameter) {
	bool pressed = false;
	while (true) {
		if (GetAsyncKeyState(TriggerBind) != 0) pressed = true; //bad way but couldn't find any better way so
		else if (pressed)
		{
			pressed = false;
			for (size_t i = 0; i < windows.size(); i++)
			{
				HWND window = windows[i];
				TypeInWindow(window, TypeMsg);
			}
		}
		Sleep(1);
	}
	return 0;
}

int main()
{
	CreateThread(0, 0, ListenHandler, 0, 0, 0);
	for (;;)
	{
		windows = AddWindowsWithClassNameToList(WindowName, windows);
		for (size_t i = 0; i < windows.size(); i++)
		{
			HWND window = windows[i];
			if (!IsWindow(window)) {
				windows[i] = NULL;
				continue;
			}
		}
		Sleep(100);
	}

	return 0;
}