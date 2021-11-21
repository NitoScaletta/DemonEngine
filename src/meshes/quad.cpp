#include <meshes/quad.h>



Quad::Quad(float pos_x, float  pos_y, float size) : velocity({0,0,0})
{
        CreateVertices(pos_x, pos_y, size);
        vao.bind();
        ebo.bind();
        vbo.bindDynamic(4);
        vao.newLayoutDynamic();
        ebo.set(indices, sizeof(int)* 6);
        vbo.loadDynamic(0, sizeof(Vertex)* 4, vertices);
        vs.initShader(VERTEX_SHADER);
        fs.initShader(FRAGMENT_SHADER);
        vs.readSourceFile("VertexQuad.glsl");
        fs.readSourceFile("QuadFragment.glsl");
        ps.compileShader(vs.id,fs.id);
        vbo.loadDynamic(0, sizeof(Vertex)* 4, vertices);

}

   void Quad::CreateVertices(float pos_x , float pos_y , float size) 
    {
        size = size/2;
        float r = Random::Float();
        float g = Random::Float(); 
        float b = Random::Float(); 
        vertices[0].setPos( pos_x - size, pos_y - size);
        vertices[0].setCol(r, g, b, 1.0f);
        vertices[1].setPos( pos_x + size, pos_y - size);
        vertices[1].setCol(r, g, b, 1.0f);
        vertices[2].setPos( pos_x + size, pos_y + size);
        vertices[2].setCol(r, g, b, 1.0f);
        vertices[3].setPos( pos_x - size, pos_y + size);
        vertices[3].setCol(r, g, b, 1.0f);
    }



void Quad::draw() 
{
    Renderer::draw(vao, ebo, ps);
}


void Quad::onUpdate(glm::mat4 viewprojmatrix)
{
    
   
    position =  position + velocity;
    glm::mat4 model =  glm::translate(glm::mat4(1.0f), position);
    //glm::mat4 model =  glm::scale(glm::mat4(1.0f), glm::vec3(0.3f,0.3f, 1.0f));
    glm::mat4 mvp = viewprojmatrix * model;
    ps.setUniMat4f("aMVP", mvp);
}
