#pragma once
#include <Core/Singleton.h>
#include <iostream>

#define LOG std::cout
#define ENDL std::endl

#define HR(x) Log::instance()->__hr(x,__FILE__,__LINE__);
#define LOG_ERROR(x,...) Log::instance()->__error(x,__FILE__,__LINE__,__VA_ARGS__)
#define LOG_WARN(x,...) Log::instance()->__warn(x,__FILE__,__LINE__,__VA_ARGS__)

class Log : public Singleton<Log>
{
public:
	void __hr(HRESULT hr,LPCSTR filename,int line);
	void __error(LPCSTR code, LPCSTR filename,int line, ...);
	void __warn(LPCSTR code, LPCSTR filename, int line, ...);

};

