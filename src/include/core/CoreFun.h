#ifndef COREFUN_H_
#define COREFUN_H_
#include "core/core.h"
#include "core/profiling/Timer.h"

namespace core{
    void createBuffer(int nquad, std::vector<Vertex>& vertices, float x, float y,
                      float size_x = 100.0f, float size_y = 100.0f, bool log = false);
    void createIndices(int nquad,std::vector<int>& indices, bool log = false);
    void ClearScreen();
    void createVerticesCube(std::vector<Vertex>& vertices, bool log = false);
    void err();
    void CreateIndices(std::vector<int>& indices, int quad_number, bool log = false);
    glm::mat4 proj3d(float ratio);
    void msg(const char* mess);
    void printvec(const char* name,glm::vec3 v);
    std::string vectostr(glm::vec3& v);
}


#endif // COREFUN_H_
