#include <windows.h>
#include <stdio.h> 

void log_errors(char* caller) {
	DWORD errCode;
	char* errMsg;
	
	errCode = GetLastError();
	
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, errCode, 0, (char*)&errMsg, 0, NULL
	);
	
	fprintf(stderr, "ERROR %d (%s): %s\n", errCode, caller, errMsg);
	
	LocalFree(errMsg);
	
	ExitProcess(errCode);
}

char* skip_program_name(char* commandLine) {
	while (*commandLine != '\0' && *commandLine && '\t' && *commandLine != ' ')
		commandLine++;
	while (*commandLine == ' ' || *commandLine == '\t')
		commandLine++;
	
	return commandLine;
}

void get_times(HANDLE hProcess) {
	FILETIME fct, fet, fkt, fut;
	SYSTEMTIME sct, set;
	
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
	} else {
		log_errors("get_times");
	}
}

PROCESS_INFORMATION create_process(void) {
	STARTUPINFO sinfo; 
	PROCESS_INFORMATION pinfo;
	char* call;
	
	GetStartupInfo(&sinfo);
	call = GetCommandLine();
	call = skip_program_name(call);
	
	if (!CreateProcess(
		NULL, call, NULL, NULL,
		TRUE, NORMAL_PRIORITY_CLASS, NULL, NULL,
		&sinfo, &pinfo
	)) {
		log_errors("create_process");
	}
	
	WaitForSingleObject(pinfo.hProcess, INFINITE);
	
	return pinfo;
}

int main(void) {
	
	PROCESS_INFORMATION pinfo;
	
	pinfo = create_process();
	get_times(pinfo.hProcess);
	
	return 0;
}