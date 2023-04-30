#pragma once
#include <Core/Singleton.h>
#include <iostream>

#define LOG std::cout
#define ENDL std::endl

#define HR(x) Log::instance()->__hr(x);
#define LOG_ERROR(x,...) Log::instance()->__error(x,__VA_ARGS__)

class Log : public Singleton<Log>
{
public:
	void __hr(HRESULT hr);
	void __error(LPCSTR code, ...);
};

