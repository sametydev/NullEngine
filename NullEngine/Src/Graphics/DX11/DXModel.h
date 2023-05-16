#pragma once
#include <Graphics/Model.h>

struct ModelNode {

    uint nIndices;
    uint nIndicesOffset;
    void* texture;
};

class DXModel :
    public Model
{
public:
    DXModel();

    void Load(LPCSTR filename);
    void Render();

    VertexBuffer* vbo;
    IndexBuffer*  ibo;

    std::vector<ModelNode> mNode;

};

