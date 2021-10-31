#pragma  once
#include "core/core.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Mesh{
    public:
        Mesh(std::vector<Vertex> verts, std::vector<int> ind, std::vector<Texture> text);
        ~Mesh(){};
        void draw(ShaderProgram& ps);

    private:
        VertexArray vao;
        VertexBuffer vbo;
        ElementBuffer ebo;
        std::vector<Texture> textures;
        std::vector<Vertex> vertices;
        std::vector<int> indices;
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;
        void Setup();
};


class Model{
    public:
        Model(){};
        Model(std::string path);
        ~Model(){};
        void load(std::string path);
        void draw();
        inline ShaderProgram* GetShaderProgram() { return &ps; }
    private:
        std::string directory;
        
        ShaderProgram ps;
        /** contiene tutte le mesh del modello/scena*/
        std::vector<Mesh> meshes;
        std::vector<Texture> loadedTexture;
        void processNode(aiNode *node, const aiScene *scene);
        Mesh processMesh(aiMesh *_mesh, const aiScene *scene);
        std::vector<Texture> loadMaterialTexture(aiMaterial *material, aiTextureType type, std::string TextureTypeName);
};