#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>




struct Transform {
	glm::vec3 Position	= glm::vec3(0);
	glm::vec3 Scale		= glm::vec3(1.0f);
	float Rotation		= 0.0f;


	Transform(glm::vec3 position, glm::vec3 scale, float rotation) : Position(position), Scale(scale), Rotation(rotation) {}
	void Rotate(const float rotation) { Rotation += rotation; }
};






namespace Direction
{
	static constexpr glm::vec3 Up    = {  0,  1, 0 };
	static constexpr glm::vec3 Down  = {  0, -1, 0 };
	static constexpr glm::vec3 Right = {  1,  0, 0 };
	static constexpr glm::vec3 Left  = { -1,  0, 0 };
}
