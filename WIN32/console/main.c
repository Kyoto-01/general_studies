#include <windows.h>

int main(void) {
	HANDLE hKeyboard, hScreen;
	DWORD oldKeyboardMode;
	char pressedKey[2];
	DWORD nBytes;
	char action[32];
	
	hKeyboard = GetStdHandle(STD_INPUT_HANDLE);
	hScreen = GetStdHandle(STD_OUTPUT_HANDLE);
	
	GetConsoleMode(hKeyboard, &oldKeyboardMode);
	system("color a && cls");
	SetConsoleMode(hKeyboard, 0);
	
	while (1) {
		ReadConsole(hKeyboard, (void*)pressedKey, 1, &nBytes, NULL);
		pressedKey[nBytes] = 0;
		
		switch (pressedKey[0]) {
			case 'q':
			case 'Q':
				system("color f");
				ExitProcess(0);
				break;
			case 'w':
			case 'W':
				lstrcpy(action, "UP");
				break;
			case 's':
			case 'S':
				lstrcpy(action, "DOWN");
				break;
			case 'a':
			case 'A':
				lstrcpy(action, "LEFT");
				break;
			case 'd':
			case 'D':
				lstrcpy(action, "RIGHT");
				break;
		}
		
		SetConsoleMode(hKeyboard, oldKeyboardMode);
		system("cls");
		SetConsoleMode(hKeyboard, 0);
		
		WriteConsole(hScreen, (void*)action, lstrlen(action), &nBytes, NULL);
	}
	
	return 0;
}