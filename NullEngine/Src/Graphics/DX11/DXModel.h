#pragma once
#include <Graphics/Model.h>

struct ModelNode {

    uint indicesNum;
    uint indicesOffset;
    uint textureIndex;
    uint baseVertex; //100 + 100
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

