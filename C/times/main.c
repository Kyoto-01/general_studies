#include <windows.h>
#include <stdio.h>

void get_times(void) {
	HANDLE hProcess;
	FILETIME fct, fet, fkt, fut;
	SYSTEMTIME sct, set;
	
	hProcess = GetCurrentProcess();

	if (GetProcessTimes(hProcess, &fct, &fet, &fkt, &fut)) {
		FileTimeToSystemTime(&fct, &sct);
		FileTimeToSystemTime(&fet, &set);
		
		printf(
			"ct = %02d/%02d/%04d %02d:%02d:%02d:%03d\n", 
			sct.wDay, sct.wMonth, sct.wYear, 
			sct.wHour, sct.wMinute, sct.wSecond, sct.wMilliseconds
		);
		printf(
			"et = %02d/%02d/%04d %02d:%02d:%02d:%03d\n",
			set.wDay, set.wMonth, set.wYear, 
			set.wHour, set.wMinute, set.wSecond, set.wMilliseconds
		);
		printf("kt = %.3f ms\n", (double)(*((ULONGLONG*)&fkt)) / 10000);
		printf("ut = %.3f ms\n", (double)(*((ULONGLONG*)&fut)) / 10000);
	}
}

void clone_process(void) {
	STARTUPINFO sinfo; 
	PROCESS_INFORMATION pinfo;
	
	GetStartupInfo(&sinfo);
	
	CreateProcess(
		NULL, NULL, NULL, NULL,
		TRUE, NORMAL_PRIORITY_CLASS, NULL, NULL,
		&sinfo, &pinfo
	);
	
	WaitForSingleObject(pinfo.hProcess, INFINITE);
	
	CloseHandle(pinfo.hProcess);
	CloseHandle(pinfo.hThread);
}

int main(void) {

	for (int i = 0; i < 100000000; ++i) {
		;
	}
	
	clone_process();
	get_times();
	
	return 0;
}