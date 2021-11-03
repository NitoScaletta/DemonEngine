#include "core/CoreFun.h"



namespace core{
    void ClearScreen()
{
    for(int i = 0; i < 200; i++)
        std::cout << '\n';
}

    void printvec(const char* name, glm::vec3 v)
    {
        std::cout << name << "x = " << v.x << ", y = " << v.y << ", z = " << v.z << '\n';
    }
    
    std::string vectostr(glm::vec3& v) 
    {
        return std::string("x = "+std::to_string(v.x)+", y = "+std::to_string(v.y)+", z = "+std::to_string(v.z)).c_str();
    }


    void createBuffer(int nquad, std::vector<Vertex>& vertices, float x, float y,
                    float size_x, float size_y, bool log)

{       
        vertices.clear();
        vertices.push_back(Vertex(x, y));
        vertices.back().setTCor(0.0f, 0.0f);
        vertices.push_back(Vertex(x + size_x, y));
        vertices.back().setTCor(1.0f, 0.0f);
        vertices.push_back(Vertex(x + size_x, y+ size_y));
        vertices.back().setTCor(1.0f, 1.0f);
        vertices.push_back(Vertex(x, y + size_y));
        vertices.back().setTCor(0.0f, 1.0f);
        x += size_x*2;

       for(int i = 4; i < nquad; i+=2)
       {
            vertices.push_back(Vertex(x, y));
            if(i+1 >= nquad) break;
            vertices.push_back(Vertex(x, y + size_y));
            x+=100;
       }

       for(int i = 0; i < vertices.size(); i++)
       {
            std::cout << i;
            vertices[i].print();
       }

}

void createIndices(int nquad,std::vector<int>& indices, bool log)
{
    //Timer timer("indices");
    int topr, botr;
    indices.clear();

    indices.push_back(0);
    indices.push_back(1);
    botr = indices.back();
    indices.push_back(2);
    topr = indices.back();
    indices.push_back(2);
    indices.push_back(3);
    indices.push_back(0);
    if(nquad > 6){
        indices.push_back(botr);
        indices.push_back(botr+3);
        indices.push_back(botr+4);
        indices.push_back(botr+4);
        indices.push_back(topr);
        indices.push_back(botr);
        topr+=3;
        botr+=3;
        for(int i = 12; i < nquad; i+=6)
        {
            indices.push_back(botr);
            indices.push_back(botr + 2);
            indices.push_back(botr + 3);
            indices.push_back(botr + 3);
            indices.push_back(topr);
            indices.push_back(botr);
            topr+=2;
            botr+=2;
        }
    }

    for(int i = 0; i <  indices.size(); i++){
        std::cout << indices[i] << " " ;
    }
    std::cout << '\n';

}


void createVerticesCube(std::vector<Vertex>& vertices, bool log)
{
    //Timer timer("cubes vertices");
    vertices.push_back(Vertex(-0.5f, -0.5f, -0.5f));//0
    vertices.back().setTCor(0.0f, 0.0f);
    vertices.back().setNormal(0.0f, 0.0f, -1.0f);
    vertices.push_back(Vertex(0.5f, -0.5f, -0.5f));
    vertices.back().setTCor(1.0f, 0.0f);
    vertices.back().setNormal(0.0f, 0.0f, -1.0f);
    vertices.push_back(Vertex(0.5f, 0.5f, -0.5f));
    vertices.back().setTCor(1.0f, 1.0f);
    vertices.back().setNormal(0.0f, 0.0f, -1.0f);
    vertices.push_back(Vertex(-0.5f, 0.5f, -0.5f));
    vertices.back().setTCor(0.0f, 1.0f);
    vertices.back().setNormal(0.0f, 0.0f, -1.0f);

    vertices.push_back(Vertex(-0.5f, -0.5f, 0.5f));//4
    vertices.back().setTCor(0.0f, 0.0f);
    vertices.back().setNormal(0.0f, 0.0f, 1.0f);
    vertices.push_back(Vertex(0.5f, -0.5f, 0.5f));
    vertices.back().setTCor(1.0f, 0.0f);
    vertices.back().setNormal(0.0f, 0.0f, 1.0f);
    vertices.push_back(Vertex(0.5f, 0.5f,  0.5f));
    vertices.back().setTCor(1.0f, 1.0f);
    vertices.back().setNormal(0.0f, 0.0f, 1.0f);
    vertices.push_back(Vertex(-0.5f, 0.5f, 0.5f));
    vertices.back().setTCor(0.0f, 1.0f);
    vertices.back().setNormal(0.0f, 0.0f, 1.0f);

    vertices.push_back(Vertex(-0.5f, -0.5f, -0.5f));//8
    vertices.back().setTCor(0.0f, 0.0f);
    vertices.back().setNormal(0.0f, -1.0f, 0.0f);
    vertices.push_back(Vertex(0.5f, -0.5f, -0.5f));
    vertices.back().setTCor(1.0f, 0.0f);
    vertices.back().setNormal(0.0f, -1.0f, 0.0f);
    vertices.push_back(Vertex(0.5f, -0.5f,  0.5f));
    vertices.back().setTCor(1.0f, 1.0f);
    vertices.back().setNormal(0.0f, -1.0f, 0.0f);
    vertices.push_back(Vertex(-0.5f, -0.5f, 0.5f));
    vertices.back().setTCor(0.0f, 1.0f);
    vertices.back().setNormal(0.0f, -1.0f, 0.0f);

    vertices.push_back(Vertex(-0.5f, 0.5f, -0.5f));//12
    vertices.back().setTCor(0.0f, 0.0f);
    vertices.back().setNormal(0.0f, 1.0f, 0.0f);
    vertices.push_back(Vertex(0.5f, 0.5f, -0.5f));
    vertices.back().setTCor(1.0f, 0.0f);
    vertices.back().setNormal(0.0f, 1.0f, 0.0f);
    vertices.push_back(Vertex(0.5f, 0.5f,  0.5f));
    vertices.back().setTCor(1.0f, 1.0f);
    vertices.back().setNormal(0.0f, 1.0f, 0.0f);
    vertices.push_back(Vertex(-0.5f, 0.5f, 0.5f));
    vertices.back().setTCor(0.0f, 1.0f);
    vertices.back().setNormal(0.0f, 1.0f, 0.0f);


    vertices.push_back(Vertex(0.5f, -0.5f, -0.5f));//16
    vertices.back().setTCor(0.0f, 0.0f);
    vertices.back().setNormal(1.0f, 0.0f, 0.0f);
    vertices.push_back(Vertex(0.5f, -0.5f,  0.5f));
    vertices.back().setTCor(1.0f, 0.0f);
    vertices.back().setNormal(1.0f, 0.0f, 0.0f);
    vertices.push_back(Vertex(0.5f, 0.5f,   0.5f));
    vertices.back().setTCor(1.0f, 1.0f);
    vertices.back().setNormal(1.0f, 0.0f, 0.0f);
    vertices.push_back(Vertex(0.5f, 0.5f, -0.5f));
    vertices.back().setTCor(0.0f, 1.0f);
    vertices.back().setNormal(1.0f, 0.0f, 0.0f);

    vertices.push_back(Vertex(-0.5f, -0.5f, -0.5f));//20
    vertices.back().setTCor(0.0f, 0.0f);
    vertices.back().setNormal(-1.0f, 0.0f, 0.0f);
    vertices.push_back(Vertex(-0.5f, -0.5f,  0.5f));
    vertices.back().setTCor(1.0f, 0.0f);
    vertices.back().setNormal(-1.0f, 0.0f, 0.0f);
    vertices.push_back(Vertex(-0.5f, 0.5f,   0.5f));
    vertices.back().setTCor(1.0f, 1.0f);
    vertices.back().setNormal(-1.0f, 0.0f, 0.0f);
    vertices.push_back(Vertex(-0.5f, 0.5f, -0.5f));
    vertices.back().setTCor(0.0f, 1.0f);
    vertices.back().setNormal(-1.0f, 0.0f, 0.0f);

    if(log)
    {
        for(int i = 0; i < vertices.size(); i++)
        {
            std::cout << i;
            vertices[i].print();

        }
    }
}

void err()
{
    static int log_number = 0;
    std::cout << "this is log n " << ++log_number << '\n';
}

void msg(const char* mess)
{
    std::cout<< mess << '\n';
}

void CreateIndices(std::vector<int>& indices, int quad_number, bool log ){
    //Timer timer("indices");
    int index = 0;
    indices.clear();
    for(int i = 0; i < quad_number; i++)
    {
       indices.push_back(index);
       indices.push_back(index+1);
       indices.push_back(index+2);
       indices.push_back(index+2);
       indices.push_back(index+3);
       indices.push_back(index);
       index =  index + 4;
    }
    if(log){
        for(int i = 0; i <  indices.size(); i++){
                std:: cout << indices[i] << " ";
                if((i+1)%6 == 0 && i != 0)
                    std::cout << '\n';
        }
        std::cout << '\n';
    }

}


    glm::mat4 proj3d(float ratio)
    {
       return glm::perspective(glm::radians(45.0f), ratio, 0.1f, 200.0f);
    }
}
