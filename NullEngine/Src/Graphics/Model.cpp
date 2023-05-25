#include <PCH.h>
#include <Graphics/Model.h>
#include <Core/FileSystem.h>
#include <Graphics/DX11/DXModel.h>
#include <Graphics/Context.h>
#include <Graphics/Buffer.h>

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

void Model::SetTexture(uint index, Texture* texture)
{
	mNodes[index].texture = texture;
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

Model* ModelCache::CreatePlane(float size)
{
	DXModel* plane = new DXModel();

	VertexPNS vertices[] = {
		{{-size,0,-size},		{0,1.f,0},	{0.f,1.f}},
		{{-size,0,size},		{0,1.f,0},	{0.0f,0.f}},
		{{size,0,size},			{0,1.f,0},	{1.f,0.f}},
		{{size,0,-size},		{0,1.f,0},	{1.f,1.f}}
	};

	uint indices[] = {
		0,1,2,0,2,3
	};

	VertexAttrib attbs[] = {
		{0,Format::Float,3,offsetof(VertexPNS,VertexPNS::position)},
		{0,Format::Float,3,offsetof(VertexPNS,VertexPNS::normal)},
		{0,Format::Float,2,offsetof(VertexPNS,VertexPNS::st)}
	};

	VertexBufferDesc vd{};
	vd.nAttrib = std::size(attbs);
	vd.pAttrib = attbs;
	vd.cbStride = sizeof(VertexPNS);
	vd.pData = vertices;
	vd.cbSize = sizeof(vertices);

	plane->vbo = BufferCache::CreateVertexBuffer(vd);

	IndexBufferDesc id{};
	id.cbSize = sizeof(indices);
	id.nIndices = std::size(indices);
	id.pData = indices;

	plane->ibo = BufferCache::CreateIndexBuffer(id);
	plane->mNodes.resize(1);
	plane->mNodes[0] = {plane->ibo->indices,0,0};

	mBuiltinModels.emplace_back(std::shared_ptr<DXModel>(plane));

	return plane;
}
