
#include <Windows.h>
using namespace std;

#include "GameSettings.h"

void SetWindowSize()
{
	HWND console = GetConsoleWindow();
	RECT ConsoleRect;
	GetWindowRect(console, &ConsoleRect); 
	MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 800, 700, TRUE);
}