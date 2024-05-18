#pragma once

//#include "tiny_obj_loader.h"
#include "Minimal.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include "glm/glm.hpp"
#include "Mesh.h"
#include "IndexBuffer.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include <vector>


class Camera;
class Model
{
public:
    Model() = default;
    Model(std::string filepath);

    int loadModel(std::string filepath);

    const std::vector<Mesh>& GetMesh();

    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
        std::string typeName);

    const std::shared_ptr<Shader>& GetShader() const { return m_Shader; }

    void PrepareMesh();
    void DrawModel(const Camera& camera);

    glm::mat4& GetModelMatrix() { return m_ModelMatrix; }
    void UpdateModelMatrix(const glm::mat4& mat) { m_ModelMatrix = mat; }

private:
    std::shared_ptr<VertexArray> m_VertexArray;
    std::shared_ptr<VertexBuffer> m_VertexBuffer;
    std::shared_ptr<IndexBuffer> m_IndexBuffer;

    std::vector<Mesh> m_Meshes;
    std::string m_Filepath;
    std::shared_ptr<Shader> m_Shader;
    glm::mat4 m_ModelMatrix = glm::mat4{ 1.0f };
};