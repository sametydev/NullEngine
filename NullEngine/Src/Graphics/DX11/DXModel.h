#pragma once
#include <Graphics/Model.h>

class DXModel :
    public Model
{
public:
    DXModel();

    void Load(LPCSTR filename);
    void Render();

    VertexBuffer* vbo;
    IndexBuffer*  ibo;

};

