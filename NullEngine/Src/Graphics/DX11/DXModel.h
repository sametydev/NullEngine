#pragma once
#include <Graphics/Model.h>
constexpr int g_instaceSize = sizeof(VertexPNTS) * 40000;

class DXModel :
    public Model
{
public:
    DXModel();
    virtual ~DXModel();
    virtual void Create(std::vector<VertexPNTS>& vertices,
        std::vector<uint>& indices
    );
    void Render();
    virtual void RenderInstanced(uint nInstance, void* data) override;


    ID3D11Buffer* mVBO = nullptr;
    ID3D11Buffer* mIBO = nullptr;
    static ID3D11Buffer* gInstanceBuffer;
    ID3D11InputLayout* mLayout = nullptr;
};

