#include <PCH.h>
#include <Core/Log.h>
#include <Wnd/WndConfig.h>

void Log::__hr(HRESULT hr)
{
	if (FAILED(hr)) {
		char* buffer = {};
		FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER|FORMAT_MESSAGE_FROM_SYSTEM|
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,hr,MAKELANGID(LANG_NEUTRAL,SUBLANG_DEFAULT),
			(LPSTR)&buffer,0,NULL
		);
		LocalFree(buffer);
		char code[256];
		sprintf_s(code,"%s\n",buffer);

		MessageBox(NULL, code, "HRESULT Error", MB_OK);
	}
}

void Log::__error(LPCSTR code, ...)
{
	va_list args;
	va_start(args,code);
	TCHAR codeBuffer[128];

	vsnprintf(codeBuffer, -1, code, args);
	va_end(args);

	uint res = MessageBox(NULL, codeBuffer, "Error", MB_OK);
	if (res == IDOK)
	{
		ExitProcess(0);
	}
}
