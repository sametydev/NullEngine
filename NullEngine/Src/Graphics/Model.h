#pragma once
struct ModelNode {
    uint nIndices;
    uint nIndicesOffset;
    Texture* texture;
};
class Model
{
public:
    Model();
    virtual ~Model();

    virtual void Render() = 0;

    uint GetNodeCount() const;
    const ModelNode* GetNodes() const;
    ModelNode* GetNode( uint index);

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

