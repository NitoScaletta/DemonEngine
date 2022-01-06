#include "Renderer/FrameBuffer.h"
#include "core/Log.h"


FrameBuffer::FrameBuffer(FrameBufferProps& fbprops)
{
    m_Props = fbprops;
	Create();
}


void FrameBuffer::bind()		
{ 
    glBindFramebuffer(GL_FRAMEBUFFER, id);
}


void FrameBuffer::unbind()	
{ 
    glBindFramebuffer(GL_FRAMEBUFFER, 0);  
}

void  FrameBuffer::Resize(FrameBufferProps& fbprops)
{
	m_Props = fbprops;
	Create();
}

void FrameBuffer::Create()
{
	if (id)
	{
		glDeleteFramebuffers(1, &id);
		glDeleteTextures(1, &color_id);
		glDeleteTextures(1, &depth_id);
	}

	glCreateFramebuffers(1, &id);
	glBindFramebuffer(GL_FRAMEBUFFER, id);
		
	glCreateTextures(GL_TEXTURE_2D, 1, &color_id);
	glBindTexture(GL_TEXTURE_2D, color_id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Props.width, m_Props.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color_id, 0);

	glCreateTextures(GL_TEXTURE_2D, 1, &depth_id);
	glBindTexture(GL_TEXTURE_2D, depth_id);
	glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_Props.width, m_Props.height);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depth_id, 0);

	if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		DE_CORE_CRITICAL("FrameBuffer was not created correctly");

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}



FrameBuffer::~FrameBuffer()
{
	glDeleteFramebuffers(1, &id);
	glDeleteTextures(1, &color_id);
	glDeleteTextures(1, &depth_id);

}
