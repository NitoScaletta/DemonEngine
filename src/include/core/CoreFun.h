#ifndef COREFUN_H_
#define COREFUN_H_
#include "core/core.h"
#include "core/profiling/Timer.h"
#include "Renderer/glObjects.h"

namespace core{
    void createIndices(int nquad,std::vector<int>& indices, bool log = false);
    void createVerticesCube(std::vector<Vertex>& vertices, bool log = false);
    void err();
    void CreateIndices(std::vector<int>& indices, int quad_number, bool log = false);
    void msg(const char* mess);
    void printvec(const char* name,glm::vec3 v);
    std::string vectostr(glm::vec3& v);
}


#endif // COREFUN_H_
