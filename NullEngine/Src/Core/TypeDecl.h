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
struct HWND__;      typedef HWND__* HWND;
struct HINSTANCE__; typedef HINSTANCE__* HINSTANCE;
struct HDC__;       typedef HDC__* HDC;
struct HGLRC_;      typedef HGLRC_* HGLRC;



//Type
typedef UINT			uint;
typedef unsigned char	byte;
typedef const char* LPCSTR;


//==================OpenGL46===================
typedef unsigned int GLenum;
typedef unsigned char GLboolean;
typedef unsigned int GLbitfield;
typedef signed char GLbyte;
typedef short GLshort;
typedef int GLint;
typedef int GLsizei;
typedef unsigned char GLubyte;
typedef unsigned short GLushort;
typedef unsigned int GLuint;
typedef float GLfloat;
typedef float GLclampf;
typedef double GLdouble;
typedef double GLclampd;
typedef void GLvoid;
//===============================================

//==================DirectX 11===================
//Device
struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11Device1;
struct ID3D11DeviceContext1;
struct IDXGISwapChain1;

//Texture
struct ID3D11RenderTargetView;
struct ID3D11DepthStencilView;
struct ID3D11Texture2D;


//Object
struct ID3D11Buffer;
struct ID3D11InputLayout;
struct ID3D11VertexShader;
struct ID3D11PixelShader;
struct ID3D11ShaderResourceView;

//States
struct ID3D11RasterizerState;
struct ID3D11SamplerState;
struct ID3D11BlendState;

struct ID3D10Blob;
typedef ID3D10Blob ID3DBlob;

struct D3D11_INPUT_ELEMENT_DESC;
//===============================================

//=================USER==========================
class Context;
class Scene;


class IndexBuffer;
class VertexBuffer;
class ConstantBuffer;

class Shader;

class Model;
class Texture;
class VertexShader;
class PixelShader;

class Camera;
class TCamera;

//===============================================


//API Type

enum class GraphicAPI {
    DirectX11,OpenGL46
};

struct Viewport {
    float x, y, w, h;
};

enum class SamplerState {
    WRAP, CLAMP
};

enum class CullMode {
    BACK,FRONT,FRONT_AND_BACK,WIREFRAME
};

//TODO : with equations
enum class BlendState {
    Transparent,Disable,Inverse
};

enum class Topolgy {
    UNDEFINED = 0,POINTLIST, LINELIST,LINESTRIP,TRIANGLELIST,TRIANGLESTRIP
};

enum class ShaderType : uint
{
    Vertex,
    Pixel,
    Hull,
    Geometry,
    Compute
};

enum class Format : int
{
    Byte,
    Int,
    Uint,
    Short,
    Float,
    Double,
};


struct VertexAttrib {
    uint slot;
    Format format;
    uint nFormat;
    uint offset;
};

struct VertexBufferDesc {
    void* pData;
    uint cbSize;
    uint cbStride;
    VertexAttrib*   pAttrib;
    uint            nAttrib;
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