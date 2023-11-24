#include "PCH.h"
#include <Graphics/DX11/DX11Config.h>
#include "Vertex.h"

const D3D11_INPUT_ELEMENT_DESC VertexPTLayout::inputLayout[2] = {
    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

const D3D11_INPUT_ELEMENT_DESC VertexPNCLayout::inputLayout[3] = {
    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

const D3D11_INPUT_ELEMENT_DESC VertexPNTLayout::inputLayout[3] = {
    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

const D3D11_INPUT_ELEMENT_DESC VertexPNTSLayout::inputLayout[4] = {
    { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    { "TEXCOORD", 1, DXGI_FORMAT_R32G32_FLOAT, 0, 36, D3D11_INPUT_PER_VERTEX_DATA, 0 }
};

const D3D11_INPUT_ELEMENT_DESC VertexPTTTInstancedLayout::inputLayout[8] = {
    {"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
    {"TEXCOORD",0,DXGI_FORMAT_R32G32B32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0},
    {"TEXCOORD",1,DXGI_FORMAT_R32G32B32_FLOAT,0,24,D3D11_INPUT_PER_VERTEX_DATA,0},
    {"TEXCOORD",2,DXGI_FORMAT_R32G32_FLOAT,0,36,D3D11_INPUT_PER_VERTEX_DATA,0},

    //Instancing 
    {"INSTANCE",0,DXGI_FORMAT_R32G32B32A32_FLOAT,1,0,D3D11_INPUT_PER_INSTANCE_DATA,1},
    {"INSTANCE",1,DXGI_FORMAT_R32G32B32A32_FLOAT,1,16,D3D11_INPUT_PER_INSTANCE_DATA,1},
    {"INSTANCE",2,DXGI_FORMAT_R32G32B32A32_FLOAT,1,32,D3D11_INPUT_PER_INSTANCE_DATA,1},
    {"INSTANCE",3,DXGI_FORMAT_R32G32B32A32_FLOAT,1,48,D3D11_INPUT_PER_INSTANCE_DATA,1}
};