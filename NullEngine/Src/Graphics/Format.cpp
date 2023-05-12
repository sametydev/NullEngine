#include <PCH.h>
#include <Graphics/Format.h>
#include <Graphics/DX11/DX11Config.h>

DXGI_FORMAT format::FormatToDX(uint count, Format format)
{
	switch (count)
	{
	case 1:
		switch (format)
		{
		case Format::Byte:
			return DXGI_FORMAT_R8_UNORM;
			break;
		case Format::Int:
			return DXGI_FORMAT_R32_SINT;
			break;
		case Format::Uint:
			return DXGI_FORMAT_R32_UINT;
			break;
		case Format::Float:
			return DXGI_FORMAT_R32_FLOAT;
			break;
		default:
			assert(0, "Failed to transform format!");
			break;
		}
		break;
	case 2:
		switch (format)
		{
		case Format::Byte:
			return DXGI_FORMAT_R8G8_UNORM;
			break;
		case Format::Int:
			return DXGI_FORMAT_R32G32_SINT;
			break;
		case Format::Uint:
			return DXGI_FORMAT_R32G32_UINT;
			break;
		case Format::Float:
			return DXGI_FORMAT_R32G32_FLOAT;
			break;
		default:
			assert(0, "Failed to transform format!");
			break;
		}
	case 3:
		switch (format)
		{
		case Format::Byte:
			assert(0, "Invalid format");
			break;
		case Format::Int:
			return DXGI_FORMAT_R32G32B32_SINT;
			break;
		case Format::Uint:
			return DXGI_FORMAT_R32G32B32_UINT;
			break;
		case Format::Float:
			return DXGI_FORMAT_R32G32B32_FLOAT;
			break;
		default:
			assert(0, "Failed to transform format!");
			break;
		}
		break;
	case 4:
		switch (format)
		{
		case Format::Byte:
			assert(0, "Invalid format");
			break;
		case Format::Int:
			return DXGI_FORMAT_R32G32B32A32_SINT;
			break;
		case Format::Uint:
			return DXGI_FORMAT_R32G32B32A32_UINT;
			break;
		case Format::Float:
			return DXGI_FORMAT_R32G32B32A32_FLOAT;
			break;
		default:
			assert(0, "Failed to transform format!");
			break;
		}
		break;
	default:
		return DXGI_FORMAT_UNKNOWN;
		break;
	}
	return DXGI_FORMAT_UNKNOWN;
}
