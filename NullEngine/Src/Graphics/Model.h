#pragma once
#include <Component/Object.h>

struct ModelNode {
    ModelNode() : nIndices(0), nIndicesOffset(0), texture(nullptr) {};
    uint nIndices;
    uint nIndicesOffset;
    Texture* texture;
};

class Model : public Renderable
{
public:
    Model();
    virtual ~Model();


    virtual void Create(std::vector<VertexPNTS>& vertices,
        std::vector<uint>& indices,Shader* shader
    ) = 0;

    virtual void RenderInstanced(uint nInstance, void* data);

    void Render() {};

    uint GetNodeCount() const;
    const ModelNode* GetNodes() const;
    ModelNode* GetNode( uint index);

    void SetTexture(uint index,Texture* texture);

    std::vector<ModelNode> mNodes;

};

class BuiltInModel : public Model {
public:
    BuiltInModel();
    virtual void Create(std::vector<VertexPNTS>& vertices,
        std::vector<uint>& indices,Shader* shader
    );
    void Render();

    VertexBuffer* vbo;
    IndexBuffer* ibo;
};

#include <unordered_map>

class ModelCache {
public:
    static Model* LoadFromFile(LPCSTR filename, Shader* shader);
    static Model* CreatePlane(float size);

    static std::unordered_map<std::string, std::shared_ptr<Model>> mCache;
    static std::vector<std::shared_ptr<Model>> mBuiltinModels;
};

