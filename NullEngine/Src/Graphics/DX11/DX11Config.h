#pragma once
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <dxgi1_3.h>
#include <wrl.h>

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")
#pragma comment(lib,"DXGI.lib")



#ifdef _DEBUG
#pragma comment(lib,"dxguid.lib")
#endif

template<typename T>
using comptr = Microsoft::WRL::ComPtr<T>;