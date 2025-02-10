#include <windows.h>
#include <stdio.h>

HANDLE screen;
CONSOLE_SCREEN_BUFFER_INFO screenInfo; 
	
void print_console_info(void) {
	screen = GetStdHandle(STD_OUTPUT_HANDLE);
	
	if (screen == INVALID_HANDLE_VALUE) {
		ExitProcess(GetLastError());
	}
	
	if (!GetConsoleScreenBufferInfo(screen, &screenInfo)) {
		ExitProcess(GetLastError());
	}

	printf("Output Buffer Width: %d\n", screenInfo.dwSize.X);
	printf("Output Buffer Height: %d\n", screenInfo.dwSize.Y);
	printf("Cursor X: %d\n", screenInfo.dwCursorPosition.X);
	printf("Cursor Y: %d\n", screenInfo.dwCursorPosition.Y);
	printf("Attributes: %d\n", screenInfo.wAttributes);
	printf("Window Rect Left: %d\n", screenInfo.srWindow.Left);
	printf("Window Rect Top: %d\n", screenInfo.srWindow.Top);
	printf("Window Rect Right: %d\n", screenInfo.srWindow.Right);
	printf("Window Rect Bottom: %d\n", screenInfo.srWindow.Bottom);
	printf("Max Window Width: %d\n", screenInfo.dwMaximumWindowSize.X);
	printf("Max Window Height: %d\n", screenInfo.dwMaximumWindowSize.Y);
	printf("\n");
}

void clear_screen(void) {
	DWORD n;
	
	FillConsoleOutputCharacter(
		screen, ' ', screenInfo.dwSize.X * screenInfo.dwSize.Y,
		(COORD){0, 0}, &n 
	);
	
	SetConsoleCursorPosition(screen, (COORD){0, 0});
}

int main(void) {
	WORD oldAttributes;
	
	print_console_info();
	oldAttributes = screenInfo.wAttributes;
	
	Sleep(3000);
	clear_screen();
	
	SetConsoleTextAttribute(screen, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	print_console_info();
	SetConsoleTextAttribute(screen, oldAttributes);
	
	return 0;
}