#ifndef __MATH_H_
#define __MATH_H_
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


static constexpr glm::mat4 IdMatrix = glm::mat4(1.0f);


struct Transform {
	glm::vec3 Position	= glm::vec3(0);
	glm::vec3 Scale		= glm::vec3(1.0f);
	float Rotation		= 0.0f;

	glm::mat4 const CalcTransformMatrix() {
		return glm::translate(glm::mat4(1.0f), Position) * glm::rotate(glm::mat4(1.0f), glm::radians(Rotation), { 0,0,1 }) * glm::scale(glm::mat4(1.0f), Scale);
	}

	Transform() {};
	Transform(glm::vec3 position, glm::vec3 scale, float rotation) : Position(position), Scale(scale), Rotation(rotation), transform(IdMatrix) {}
	void Rotate(const float rotation) { Rotation += rotation; }
	operator const glm::mat4& () { transform = CalcTransformMatrix(); return transform; }
		
	private:
		glm::mat4 transform = IdMatrix;
};






namespace Direction
{
	static constexpr glm::vec3 Up    = {  0,  1, 0 };
	static constexpr glm::vec3 Down  = {  0, -1, 0 };
	static constexpr glm::vec3 Right = {  1,  0, 0 };
	static constexpr glm::vec3 Left  = { -1,  0, 0 };
}



#endif
