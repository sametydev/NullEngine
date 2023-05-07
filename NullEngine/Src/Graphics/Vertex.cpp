#include <PCH.h>
#include <Graphics/Vertex.h>

D3D11_INPUT_ELEMENT_DESC VertexPC::elements[] = {

	{
	"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,
	offsetof(VertexPC,VertexPC::position),D3D11_INPUT_PER_VERTEX_DATA,0
	},
	{
	"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,0,
	offsetof(VertexPC,VertexPC::st),D3D11_INPUT_PER_VERTEX_DATA,0
	}
};

int VertexPC::nElements = ARRAYSIZE(elements);