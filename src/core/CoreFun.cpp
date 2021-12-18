#include "core/CoreFun.h"
#include "core/Log.h"



namespace core{

    void printvec(const char* name, glm::vec3 v)
    {
        DE_CORE_TRACE("{3} ----> x= {0}, y= {1} z = {2}", v.x, v.y, v.z, name);
    }
    
    std::string vectostr(glm::vec3& v) 
    {
        return std::string("x = "+std::to_string(v.x)+", y = "+std::to_string(v.y)+", z = "+std::to_string(v.z)).c_str();
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
       DE_CORE_TRACE("{0}", indices[i]);
    }

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
            DE_CORE_TRACE("{0}", i);
            vertices[i].print();

        }
    }
}

void err()
{
    static int log_number = 0;
    DE_CORE_TRACE("this is log n ", ++log_number);
}

void msg(const char* mess)
{
    DE_CORE_TRACE(mess);
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
                DE_CORE_TRACE("{0}", indices[i]);
        }
    }

}

}
