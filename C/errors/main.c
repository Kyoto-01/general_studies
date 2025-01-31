#include <stdio.h>
#include <windows.h>
#include <locale.h>

int main(void) {
		
	setlocale(LC_ALL, "Portuguese_Brasil");
	// chcp 65001 in cmd
	
	char lastErr = GetLastError();
	
	char *errMsg;
	
	DWORD lenErrMsg = FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, lastErr, 0, (char *)&errMsg, 0, NULL
	);
	
	printf(
		"Error %d (%d chars message): %s.\n",
		lastErr, lenErrMsg, errMsg
	);
	
	LocalFree(errMsg);
	
	return 0;
}