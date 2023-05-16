#include <PCH.h>
#include <Graphics/Model.h>
#include <Core/FileSystem.h>
#include <Graphics/DX11/DXModel.h>

Model::Model()
{
}

Model::~Model()
{
}

uint Model::GetNodeCount() const
{
	return (uint)mNodes.size();
}

const ModelNode* Model::GetNodes() const
{
	return mNodes.data();
}

ModelNode* Model::GetNode(uint index)
{
	assert((index < mNodes.size()) && "out of bound node index");
	return &mNodes[index];
}

std::unordered_map<std::string, std::shared_ptr<Model>> ModelCache::mCache;
std::vector<std::shared_ptr<Model>>						ModelCache::mBuiltinModels;
Model* ModelCache::LoadFromFile(LPCSTR filename)
{

	if (!FileSystem::IsExistsFile(filename))
	{
		LOG_ERROR("%s is not found", filename);
	}
	auto found = mCache.find(filename);
	if (found != mCache.end())
	{
		return found->second.get();
	}

	auto model = std::make_shared<DXModel>();

	model->Load(filename);

	mCache.insert(std::make_pair(filename, model));

	return model.get();
}
