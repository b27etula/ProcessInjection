#include <Windows.h>

void showMessageBox(const CHAR* lpText, const CHAR* lpCaption)
{
	MessageBoxA(NULL, lpText, lpCaption, MB_OK);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	const CHAR* lpText    = "Test";
	const CHAR* lpCaption = "MessageBoxA";

	while (TRUE)
		showMessageBox(lpText, lpCaption);
	return 0;
}