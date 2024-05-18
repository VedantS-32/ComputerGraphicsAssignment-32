#pragma once

//#include "tiny_obj_loader.h"
#include "Minimal.h"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include "glm/glm.hpp"

#include "Texture.h"

#include <vector>

struct Vertex {
    glm::vec3 m_position;
    glm::vec3 m_normal;
    glm::vec2 m_texcoords;
};

class Mesh
{
public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
    {
        m_Vertices = vertices;
        m_Indices = indices;
        m_Textures = textures;
    }

    std::vector<Vertex>& GetVertices() { return m_Vertices; }
    std::vector<uint32_t>& GetIndices() { return m_Indices; }

    std::vector<Vertex> m_Vertices;
    std::vector<uint32_t> m_Indices;
    std::vector<Texture> m_Textures;
};