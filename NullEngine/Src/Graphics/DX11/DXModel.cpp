#include <PCH.h>
#include <Graphics/DX11/DXModel.h>
#include <Core/FileSystem.h>
#include <Graphics/Buffer.h>
#include <Graphics/Context.h>
#include <Graphics/Texture.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

DXModel::DXModel():ibo(nullptr),vbo(nullptr)
{

}

void DXModel::Load(LPCSTR filename)
{
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
	std::vector<uint>	  indices;

	uint numMesh = scene->mNumMeshes;
	mNodes.resize(numMesh);

	for (int index = 0; index < numMesh; index++)
	{
		const aiMesh* mesh = scene->mMeshes[index];
		uint nVertices = mesh->mNumVertices;

		for (int i = 0; i < nVertices; i++){

			VertexPNS vtx;
			memcpy(&vtx.position, &mesh->mVertices[i], sizeof(vec3f));
			memcpy(&vtx.normal, &mesh->mNormals[i], sizeof(vec3f));

			if (mesh->mTextureCoords[0])
			{
				memcpy(&vtx.st, &mesh->mTextureCoords[0][i],sizeof(vec2f));
			}

			vertices.emplace_back(vtx);
		}
		uint nIndices = mesh->mNumFaces * 3;
		ModelNode* nodes = mNodes.data();

		
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

	
	VertexAttrib attrb[] = {

		{0,Format::Float,3,offsetof(VertexPNS,VertexPNS::position)},
		{0,Format::Float,3,offsetof(VertexPNS,VertexPNS::normal)},
		{0,Format::Float,2,offsetof(VertexPNS,VertexPNS::st)}

	};

	VertexBufferDesc vd{};

	vd.cbSize		= sizeof(VertexPNS) * (uint)vertices.size();
	vd.cbStride		= sizeof(VertexPNS);
	vd.pData		= vertices.data();
	vd.pAttrib		= attrb;
	vd.nAttrib		= std::size(attrb);

	vbo = BufferCache::CreateVertexBuffer(vd);

	IndexBufferDesc id{};
	id.cbSize = indices.size() * sizeof(uint);
	id.nIndices = indices.size();
	id.pData = indices.data();
	

	ibo = BufferCache::CreateIndexBuffer(id);

}

void DXModel::Render()
{
	vbo->BindPipeline(0);
	ibo->BindPipeline(0);

	for (int i = 0; i < GetNodeCount(); i++)
	{
		ModelNode*  node = GetNode(i);
		if (node->texture)
		{
			node->texture->BindPipeline(0);
		}
		gContext->DrawIndexed(node->nIndices, node->nIndicesOffset, 0);
	}
}
