#include <string.h>
#include <windows.h>
#include <tlhelp32.h>


DWORD getProcessIdByName(const CHAR* processName)
{
    PROCESSENTRY32 processEntry;
    HANDLE hSnapshot;
    DWORD dwProcessId = NULL;

    if ((hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0)) != INVALID_HANDLE_VALUE)
    {
        processEntry.dwSize = sizeof(PROCESSENTRY32);
        Process32First(hSnapshot, &processEntry);
        do
        {
            if (!strcmp(processEntry.szExeFile, processName))
                dwProcessId = processEntry.th32ProcessID;
        } while (Process32Next(hSnapshot, &processEntry));
        CloseHandle(hSnapshot);
    }

    return dwProcessId;
}

DWORD getModuleBase(const CHAR* lpModuleName, DWORD dwProcessId)
{
    MODULEENTRY32 lpModuleEntry = { 0 };
    HANDLE hSnapshot;
    DWORD moduleBase = NULL;

    if ((hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwProcessId)) != NULL)
    {
        lpModuleEntry.dwSize = sizeof(lpModuleEntry);
        Module32First(hSnapshot, &lpModuleEntry);
        do
        {
            if (!strcmp(lpModuleEntry.szModule, lpModuleName))
            {
                moduleBase = (DWORD)lpModuleEntry.modBaseAddr;
            }
        } while (Module32Next(hSnapshot, &lpModuleEntry));

        CloseHandle(hSnapshot);
    }

    return moduleBase;
}