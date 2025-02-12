#include <windows.h>

int main(void) {
	HANDLE hFile;
	
	hFile = CreateFile(
		"C:\\tests\\test001.txt",
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		CREATE_NEW,
		FILE_ATTRIBUTE_TEMPORARY,
		NULL
	);
	
	if (hFile == INVALID_HANDLE_VALUE) {
		return EXIT_FAILURE;
	}
	
	CloseHandle(hFile);
	
	return EXIT_SUCCESS;
}