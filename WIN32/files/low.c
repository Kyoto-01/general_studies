#include "ntapi.h"
#include <windows.h>

int main()
{
    HANDLE hFile;
    NTSTATUS status;
    UNICODE_STRING fpathU;
    OBJECT_ATTRIBUTES obj;
    IO_STATUS_BLOCK isb;
    LPCWSTR filepath = L"\\??\\\\C:\\tests\\test002.txt";

    // resolve functions addresses
    pNtCreateFile NtCreateFile =
        (pNtCreateFile)GetProcAddress(GetModuleHandle("ntdll.dll"), "NtCreateFile");
    pRtlInitUnicodeString RtlInitUnicodeString = (pRtlInitUnicodeString)GetProcAddress(
        GetModuleHandle("ntdll.dll"),
        "RtlInitUnicodeString");

    // add wide char string to UNICODE_STRING struct
    RtlInitUnicodeString(&fpathU, filepath);

    // add filepath to object attributes
    InitializeObjectAttributes(&obj, &fpathU, OBJ_CASE_INSENSITIVE, NULL, NULL);

    // create file with native API
    status = NtCreateFile(
        &hFile,
        FILE_GENERIC_WRITE,
        &obj,
        &isb,
        0,
        FILE_ATTRIBUTE_NORMAL,
        FILE_SHARE_READ,
        FILE_OVERWRITE_IF,
        FILE_NON_DIRECTORY_FILE,
        NULL,
        0);

    if (!NT_SUCCESS(status)) {
        CloseHandle(hFile);
        return EXIT_FAILURE;
    }

    CloseHandle(hFile);
    return EXIT_SUCCESS;
}