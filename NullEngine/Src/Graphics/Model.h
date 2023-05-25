#pragma once
#include <Component/Object.h>

struct ModelNode {
    uint nIndices;
    uint nIndicesOffset;
    Texture* texture;
};

class Model : public Renderable
{
public:
    Model();
    virtual ~Model();


    virtual void Create(std::vector<VertexPNS>& vertices,
        std::vector<uint>& indices
    ) = 0;

    void Render() {};

    uint GetNodeCount() const;
    const ModelNode* GetNodes() const;
    ModelNode* GetNode( uint index);

    void SetTexture(uint index,Texture* texture);

    std::vector<ModelNode> mNodes;

};

#include <unordered_map>

class ModelCache {
public:
    static Model* LoadFromFile(LPCSTR filename);
    static Model* CreatePlane(float size);

    static std::unordered_map<std::string, std::shared_ptr<Model>> mCache;
    static std::vector<std::shared_ptr<Model>> mBuiltinModels;
};

