#include "dllDemo.h"
char g_strHost[MAX_PATH];
DWORD g_dwPort;
struct Connect_Address
{
	DWORD dwstact;
	char strIP[MAX_PATH];
	int nPort;
}g_myAddress = { 0x1789714,"",0 };

extern "C" _declspec(dllexport) void __cdecl rundll32dllfun(HWND hwnd, HINSTANCE hinst, LPSTR lpszCmdLine, int nCmdShow)
{
	strcpy(g_strHost, g_myAddress.strIP);
	g_dwPort = g_myAddress.nPort;
	CString msg;
	msg.Format("%s:%d", g_strHost, g_dwPort);
	MessageBox(NULL, msg, lpszCmdLine, MB_OK);
	return;
}