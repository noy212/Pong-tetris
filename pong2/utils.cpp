#include <Windows.h>
#include "utils.h"

BOOL gotoxy(const WORD x, const WORD y) {
	COORD xy;
	xy.X = x;
	xy.Y = y;
	return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
}


void hideConsoleCursor(bool hideFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = !hideFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

void setColor(COLOR color) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// pick the colorattribute
	SetConsoleTextAttribute(hConsole, (int)color);
}