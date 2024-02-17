#pragma once

//#include "tiny_obj_loader.h"
#include "Minimal.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include "glm/glm.hpp"
#include "Mesh.h"

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

#include <vector>


class Model
{
public:
    int loadModel(std::string filepath);
    const std::vector<Vertex>& getVertices() const;
    const std::vector<unsigned int>& getIndices() const;

    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type,
        std::string typeName);

private:
    std::vector<Mesh> m_Meshes;
    std::string m_Filepath;
};