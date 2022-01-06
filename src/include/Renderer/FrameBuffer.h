#pragma once
#include <glad/glad.h>
#include <iostream>


struct FrameBufferProps
{
	uint32_t width, height;

};

class FrameBuffer
{
public:
	FrameBuffer(FrameBufferProps& fbprops);
	~FrameBuffer();
	void bind();
	void unbind();
	void Resize(FrameBufferProps& props);
	uint32_t GetColorAttachmentId() { return color_id; }
private:
	uint32_t id, color_id, depth_id;
	FrameBufferProps m_Props;

	void Create();

};