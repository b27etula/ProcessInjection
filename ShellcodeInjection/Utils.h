#include <windows.h>
#pragma once


DWORD getProcessIdByName(const CHAR* processName);

DWORD getModuleBase(const CHAR* lpModuleName, DWORD dwProcessId);
