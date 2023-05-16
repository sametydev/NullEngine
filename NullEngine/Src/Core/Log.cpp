#include <PCH.h>
#include <Core/Log.h>
#include <Wnd/WndConfig.h>

void Log::__hr(HRESULT hr, LPCSTR filename, int line)
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
		TCHAR totalCuffer[256];
		filename = (::strrchr(filename,'\\') + 1);
		sprintf_s(totalCuffer,"%s\nfile: %s\n line %d\n\n",buffer,filename,line);

		if (MessageBox(NULL, totalCuffer, "HRESULT Error", MB_OK)) {
			ExitProcess(0);
		}

	}
}

void Log::__error(LPCSTR code, LPCSTR filename, int line, ...)
{
	va_list args;
	va_start(args,code);
	TCHAR codeBuffer[128]{};

	vsnprintf_s(codeBuffer, -1, code, args);

	filename = (::strchr(filename,'\\')+1);
	TCHAR totalBuffer[256]{};

	sprintf_s(totalBuffer,"%s\nfile: %s\n line %d\n\n",codeBuffer,filename,line);
	va_end(args);

	uint res = MessageBox(NULL, codeBuffer, "Error", MB_OK | MB_ICONERROR);
	if (res == IDOK)
	{
		ExitProcess(0);
	}
}

void Log::__warn(LPCSTR code, LPCSTR filename, int line, ...)
{
	va_list args;
	va_start(args, code);
	TCHAR codeBuffer[128]{};

	vsnprintf_s(codeBuffer, -1, code, args);
	filename = (::strchr(filename, '\\') + 1);
	TCHAR totalBuffer[256]{};

	sprintf_s(totalBuffer, "%s\nfile: %s\n line %d\n\n", codeBuffer, filename, line);
	va_end(args);

	uint res = MessageBox(NULL, codeBuffer, "Warning", MB_CANCELTRYCONTINUE | MB_ICONWARNING);
	
	
	if (res == IDCANCEL)
	{
		ExitProcess(0);
	}
}
