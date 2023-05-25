#pragma once
#include <Graphics/Model.h>

class DXModel :
    public Model
{
public:
    DXModel();
    virtual ~DXModel();
    virtual void Create(std::vector<VertexPNS>& vertices,
        std::vector<uint>& indices
    );
    void Render();

    ID3D11Buffer* mVBO = nullptr;
    ID3D11Buffer* mIBO = nullptr;
    static ID3D11Buffer* gInstanceBuffer;
    ID3D11InputLayout* mLayout = nullptr;
};

