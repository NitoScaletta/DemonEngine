#pragma  once
#include "core.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Mesh{
    public:
    Mesh(std::vector<Vertex> verts, std::vector<int> ind, Texture* diff, Texture* spec);
    ~Mesh(){};


    private:
    VertexArray vao;
    VertexBuffer vbo;
    ElementBuffer ebo;
    Texture *tDiffuse, *tSpecular;
    std::vector<Vertex> vertices;
    std::vector<int> indices;
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
    void Setup();
};


class Model{
    public:
        Model();
        ~Model();
    private:
        



};