#include "meshes/Mesh.h"
#include <string.h>
Mesh::Mesh(std::vector<Vertex> verts, std::vector<int> ind, std::vector<Texture> text) 
:   vertices(verts),
    indices(ind),
    textures(text)
{
    Setup();
}

void Mesh::draw(ShaderProgram& ps) 
{
    Renderer renderer;
    renderer.draw(vao, ebo, ps);
    
}

void Mesh::Setup() 
{
    vao.bind();
    ebo.bind();
    ebo.set(indices.data(), sizeof(int)*indices.size());
    vbo.bindDynamic(indices.size());
    vbo.loadDynamic(0, sizeof(Vertex)*vertices.size(), vertices.data());
    vao.newLayoutDynamic();

}

Model::Model(std::string path) 
{
    load(path);
    Shader vs,fs;
    loadedTexture[0].SetTextureID(GL_TEXTURE0);
    loadedTexture[1].SetTextureID(GL_TEXTURE1);
    loadedTexture[0].active();
    loadedTexture[1].active();
    vs.initShader(VertexType::VERTEX);
    fs.initShader(VertexType::FRAGMENT);
    vs.readSourceFile("vertex.txt");
    fs.readSourceFile("FragmentModel.glsl");
    ps.compileShader(vs.id, fs.id);
}


void Model::load(std::string path) 
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
    {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }
    directory = path.substr(0, path.find_last_of('/'));
    processNode(scene->mRootNode, scene);

}

void Model::draw() 
{
    for(int32_t i = 0; i < meshes.size(); i++)
        meshes[i].draw(ps);
}


void Model::processNode(aiNode *node, const aiScene *scene) 
{
    for(int32_t i = 0; i< node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh,scene));
    }
    for(int32_t i = 0; i< node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }

}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene) 
{
    std::vector<Vertex> vertices;
    std::vector<int> indices;
    std::vector<Texture> textures;
    for(int32_t i = 0; i< mesh->mNumVertices; i++)
    {
        vertices.push_back(Vertex(mesh->mVertices[i]));
        vertices.back().setNormal(mesh->mNormals[i]);
        if(mesh->mTextureCoords[0])
        {
            vertices.back().setTCor(mesh->mTextureCoords[0][i]);
        }
        else
        {
            vertices.back().setTCor(0,0);
        }
    }
    
    for(int32_t i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace *face = &mesh->mFaces[i];
        for(int16_t j = 0; j < face->mNumIndices; j++)
        {
            indices.push_back(face->mIndices[j]);
        }
    }

    if(mesh->mMaterialIndex > 0)
    {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        textures = loadMaterialTexture(material, aiTextureType::aiTextureType_DIFFUSE,"texture_diffuse");
        std::vector<Texture> specular = loadMaterialTexture(material, aiTextureType::aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specular.begin(),specular.end());
    } 
    return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadMaterialTexture(aiMaterial *material, aiTextureType type, std::string TextureTypeName) 
{
    std::vector<Texture> textures;
    std::string dir = "backpack/";
    for(int32_t i = 0; i<material->GetTextureCount(type); i++)
    {
        aiString matStr;
        material->GetTexture(type, i,&matStr);
        bool skip = false;
        std::string temp = dir+matStr.C_Str();
        for (int16_t j = 0; j<loadedTexture.size(); j++)
        {
            if(strcmp(temp.c_str(), loadedTexture[j].GetPath()) == 0)
            {
                skip = true;
                textures.push_back(loadedTexture[j]);
                break;
            }
        }
        if(!skip)
        {
            Texture _Texture;
            std::string filepath = directory + "/" + matStr.C_Str();
            _Texture.Set(filepath.c_str());
            _Texture.SetType(TextureTypeName.c_str());
            textures.push_back(_Texture);
            loadedTexture.push_back(_Texture);
        }
    }
    return textures;
}
