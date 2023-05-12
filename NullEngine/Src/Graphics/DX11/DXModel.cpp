#include <PCH.h>
#include <Graphics/DX11/DXModel.h>
#include <Core/FileSystem.h>
#include <Graphics/Buffer.h>
#include <Graphics/Context.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

DXModel::DXModel()
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

	std::vector<VertexPC> vertices;
	std::vector<uint>	  indices;

	uint numMesh = scene->mNumMeshes;
	mNode.resize(numMesh);

	for (int index = 0; index < numMesh; index++)
	{
		const aiMesh* mesh = scene->mMeshes[index];
		uint nVertices = mesh->mNumVertices;

		for (int i = 0; i < nVertices; i++){

			VertexPC vtx;
			memcpy(&vtx.position, &mesh->mVertices[i], sizeof(vec3f));

			if (mesh->mTextureCoords[0])
			{
				memcpy(&vtx.st, &mesh->mTextureCoords[0][i],sizeof(vec2f));
			}

			vertices.emplace_back(vtx);
		}
		uint nIndices = mesh->mNumFaces * 3;
		ModelNode* nodes = mNode.data();

		nodes[index].baseVertex += mesh->mNumVertices;
		//node.indicesOffset += //first must be 0
		//	index == 0 ? 0 : ()
		
		nodes[index].indicesOffset += (index > 0) ? nodes[index - 1].indicesNum :
			0;
		nodes[index].indicesNum = nIndices;
		for (int i = 0; i < mesh->mNumFaces; i++)
		{
			//face indices couldnt over 3
			const aiFace* face = &mesh->mFaces[i];
			if (face->mNumIndices > 3)
			{
				LOG_ERROR("Mesh is not trangular");
			}
			indices.emplace_back(face->mIndices[0]);
			indices.emplace_back(face->mIndices[1]);
			indices.emplace_back(face->mIndices[2]);
		}
	}

	VertexBufferDesc vd{};

	vd.cbSize		= sizeof(VertexPC) * vertices.size();
	vd.cbStride = sizeof(VertexPC);
	vd.pData = vertices.data();
	//desc.indices	= indices.size();

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

	for (int i = 0; i < mNode.size(); i++)
	{
		auto node = &mNode[i];
		if (node->texture)
		{

		}

		//gDXContext->DrawIndexed(node->indicesNum, node->indicesOffset, 0);
	}
}
