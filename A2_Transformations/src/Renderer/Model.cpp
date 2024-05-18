#include "Model.h"

#include "stb_image.h"
#include <unordered_map>

#include "Camera.h"
#include "BufferLayout.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>

Model::Model(std::string filepath)
	: m_Filepath(filepath)
{
	m_Shader = std::make_shared<Shader>("shader/SimpleLighting.vert", "shader/SimpleLighting.frag");
	PrepareMesh();
}

int Model::loadModel(std::string filepath)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		//print("ERROR::ASSIMP::" << import.GetErrorString());
		return -1;
	}
	m_Filepath = filepath.substr(0, filepath.find_last_of('/'));

	processNode(scene->mRootNode, scene);

	return 0;
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	// process all the node's meshes (if any)
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		m_Meshes.push_back(processMesh(mesh, scene));
	}
	// then do the same for each of its children
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		// process vertex positions, normals and texture coordinates
		glm::vec3 vector;
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.m_position = vector;

		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.m_normal = vector;

		if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
		{
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.m_texcoords = vec;
		}
		else
			vertex.m_texcoords = glm::vec2(0.0f, 0.0f);
		
		vertices.push_back(vertex);
	}
	// process indices
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}
		// process material
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<Texture> diffuseMaps = loadMaterialTextures(material,
			aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		std::vector<Texture> specularMaps = loadMaterialTextures(material,
			aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}

	return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
	std::vector<Texture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		Texture texture(str.C_Str());
		textures.push_back(texture);
	}
	return textures;
}

void Model::PrepareMesh()
{
	loadModel(m_Filepath);

	m_VertexArray = std::make_shared<VertexArray>();

	m_VertexArray->Bind();

	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

	for (auto& mesh : m_Meshes)
	{
		for (auto& vertex : mesh.GetVertices())
			vertices.push_back(vertex);
		for (auto& index : mesh.GetIndices())
			indices.push_back(index);
	}

	m_VertexBuffer = std::make_shared<VertexBuffer>((void*)vertices.data(), (uint32_t)vertices.size() * sizeof(Vertex));
	print("Vertices size: " << (uint32_t)vertices.size() * sizeof(Vertex));

	BufferLayout layout;
	layout.Push<float>(0, 3, sizeof(Vertex));
	m_VertexArray->LinkAttrib(*m_VertexBuffer, layout, (void*)0);
	layout.Push<float>(1, 3, sizeof(Vertex));
	m_VertexArray->LinkAttrib(*m_VertexBuffer, layout, (void*)offsetof(Vertex, m_normal));
	layout.Push<float>(2, 2, sizeof(Vertex));
	m_VertexArray->LinkAttrib(*m_VertexBuffer, layout, (void*)offsetof(Vertex, m_texcoords));

	m_IndexBuffer = std::make_shared<IndexBuffer>(indices.data(), (uint32_t)indices.size());
	print("Indices count: " << indices.size());
}

void Model::DrawModel(const Camera& camera)
{
	glm::mat4 modelView = camera.m_ViewMatrix * m_ModelMatrix;
	glm::mat4 mvp = camera.GetProjection() * camera.m_ViewMatrix * m_ModelMatrix;
	glm::vec3 cameraPosition = camera.GetPosition();

	m_Shader->Bind();
	m_Shader->SetUniform1i("u_Texture", 0);
	m_Shader->SetUniformMat4f("u_ModelView", camera.m_ViewMatrix * m_ModelMatrix);
	m_Shader->SetUniformMat4f("u_MVP", mvp);
	m_Shader->SetUniform3f("u_CameraPosition", cameraPosition.x, cameraPosition.y, cameraPosition.z);

	Renderer::DrawIndexed(m_VertexArray, m_VertexBuffer, m_IndexBuffer->GetCount());
}

const std::vector<Mesh>& Model::GetMesh()
{
	return m_Meshes;
}
