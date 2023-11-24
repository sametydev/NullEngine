#pragma once
#include <Core/TypeDecl.h>
//P = POS
//C = COLOR
//N = NORMAL
//T = TEXTURE
//S = SIZE

struct VertexPTLayout
{
    VertexPTLayout() = default;
    static const D3D11_INPUT_ELEMENT_DESC inputLayout[2];
};

struct VertexPNCLayout
{
    VertexPNCLayout() = default;
    static const D3D11_INPUT_ELEMENT_DESC inputLayout[3];
};


struct VertexPNTLayout
{
    VertexPNTLayout() = default;
    static const D3D11_INPUT_ELEMENT_DESC inputLayout[3];
};

struct VertexPNTSLayout
{
    VertexPNTSLayout() = default;
    static const D3D11_INPUT_ELEMENT_DESC inputLayout[4];
};

struct VertexPTTTInstancedLayout
{
    VertexPTTTInstancedLayout() = default;

    static const D3D11_INPUT_ELEMENT_DESC inputLayout[8];
};