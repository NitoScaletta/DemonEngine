#include "Mesh.h"
Mesh::Mesh(std::vector<Vertex> verts, std::vector<int> ind, Texture* diff, Texture* spec) 
:   vertices(verts),
    indices(ind),
    tDiffuse(diff),
    tSpecular(spec)
{
    Setup();
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
