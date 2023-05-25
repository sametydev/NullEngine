#include <PCH.h>
#include <Graphics/Model.h>
#include <Core/FileSystem.h>
#include <Graphics/DX11/DXModel.h>
#include <Graphics/Context.h>
#include <Graphics/Buffer.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

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

	LoadModelFromAssimp(filename, model.get());

	mCache.insert(std::make_pair(filename, model));

	return model.get();
}

Model* ModelCache::CreatePlane(float size)
{
	/*DXModel* plane = new DXModel();

	std::vector<VertexPNS> vertices = {
		{{-size,0,-size},		{0,1.f,0},	{0.f,1.f}},
		{{-size,0,size},		{0,1.f,0},	{0.0f,0.f}},
		{{size,0,size},			{0,1.f,0},	{1.f,0.f}},
		{{size,0,-size},		{0,1.f,0},	{1.f,1.f}}
	};

	std::vector<uint> indices = {
		0,1,2,0,2,3
	};

	plane->Create(vertices, indices);

	mBuiltinModels.emplace_back(std::shared_ptr<DXModel>(plane));

	return plane;*/
	return nullptr;
}


void LoadModelFromAssimp(LPCSTR filename,
	Model* model) {

	using namespace Assimp;

	if (!FileSystem::IsExistsFile(filename))
	{
		LOG_ERROR("Failed to load model, model is not exists : %s", filename);
	}

	Importer importer;
	importer.SetPropertyInteger(AI_CONFIG_PP_SBP_REMOVE,
		aiPrimitiveType_LINE | aiPrimitiveType_POINT);

	const aiScene* scene = importer.ReadFile(filename,
		aiProcess_ConvertToLeftHanded | aiProcess_Triangulate |
		aiProcess_ImproveCacheLocality | aiProcess_SortByPType
	);

	if (!scene)
	{
		LOG_ERROR("Failed to load model scene");
	}

	std::vector<VertexPNS> vertices;
	std::vector<uint> indices;

	uint numMesh = scene->mNumMeshes;
	model->mNodes.resize(numMesh);

	for (int index = 0; index < numMesh; index++)
	{
		const aiMesh* mesh = scene->mMeshes[index];
		uint nVertices = mesh->mNumVertices;

		for (int i = 0; i < nVertices; i++) {

			VertexPNS vtx;
			memcpy(&vtx.position, &mesh->mVertices[i], sizeof(vec3f));
			memcpy(&vtx.normal, &mesh->mNormals[i], sizeof(vec3f));

			if (mesh->mTextureCoords[0])
			{
				memcpy(&vtx.st, &mesh->mTextureCoords[0][i], sizeof(vec2f));
			}

			vertices.emplace_back(vtx);
		}
		uint nIndices = mesh->mNumFaces * 3;
		ModelNode* nodes = model->mNodes.data();


		nodes[index].nIndicesOffset += (index > 0) ? nodes[index - 1].nIndices : 0;
		nodes[index].nIndices = nIndices;
		int offset = nodes[index].nIndicesOffset;

		for (int i = 0; i < mesh->mNumFaces; i++)
		{
			const aiFace* face = &mesh->mFaces[i];
			if (face->mNumIndices > 3)
			{
				LOG_ERROR("Mesh is not triangular");
			}
			indices.emplace_back(face->mIndices[0] + offset);
			indices.emplace_back(face->mIndices[1] + offset);
			indices.emplace_back(face->mIndices[2] + offset);
		}
	}

	model->Create(vertices,indices);
}