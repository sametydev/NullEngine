#pragma once

//Win32
#define CALLBACK		__stdcall
#define WINAPI			__stdcall
#define APIENTRY		WINAPI

typedef unsigned int		UINT;
typedef unsigned long		DWORD;
typedef int					BOOL;
typedef unsigned char		BYTE;
typedef unsigned short		WORD;
typedef float				FLOAT;
typedef void* LPVOID;
typedef const char* LPCSTR;
typedef char* LPSTR;

#if defined(_WIN64)
typedef __int64				INT_PTR;
typedef unsigned __int64	UINT_PTR;
typedef __int64				LONG_PTR;
typedef unsigned __int64	ULONG_PTR;
#else
typedef int					INT_PTR;
typedef unsigned int		UINT_PTR;
typedef long				LONG_PTR;
typedef unsigned long		ULONG_PTR;
#endif

typedef UINT_PTR		WPARAM;
typedef LONG_PTR		LPARAM;
typedef LONG_PTR		LRESULT;
typedef long			HRESULT;


typedef void* HANDLE;
struct HWND__; typedef HWND__* HWND;
struct HINSTANCE__; typedef HINSTANCE__* HINSTANCE;
struct HDC__; typedef HDC__* HDC;


//DirectX


//Rype
typedef UINT			uint;
typedef unsigned char	byte;
typedef const char* LPCSTR;



//==================DirectX 11===================
struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11Device1;
struct ID3D11DeviceContext1;
struct IDXGISwapChain1;
struct ID3D11RenderTargetView;
struct ID3D11DepthStencilView;
struct ID3D11Texture2D;
struct ID3D11RasterizerState;
struct D3D11_INPUT_ELEMENT_DESC;
struct ID3D11VertexShader;
struct ID3D11PixelShader;
struct ID3D11ShaderResourceView;
struct ID3D10Blob;
struct ID3D11Buffer;
struct ID3D11InputLayout;
struct ID3D11SamplerState;
typedef ID3D10Blob ID3DBlob;
//===============================================

class Context;
class Scene;

class DXBuffer;
class DXVertexBuffer;
class DXIndexBuffer;
class DXConstantMapBuffer;
class DXConstantBuffer;
class DXTexture;
class DXModel;

class Texture;
class IShader;
class VertexShader;
class PixelShader;


//API Type
struct Viewport {
    float x, y, w, h;
};

enum SamplerState {
    WRAP, CLAMP
};

struct VertexBufferDesc {
    void* pData;
    uint cbSize;
    uint cbStride;
};

struct IndexBufferDesc {
    void* pData;
    uint    cbSize;
    uint    nIndices;
};

struct ConstantBufferDesc {
    void* pData;
    uint    cbSize;
};