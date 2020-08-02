#include "pch.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>
#include "Alien/Renderer/Renderer.h"

namespace Alien {

	/////////////////////////////////////////////////////////////
	// VertexBuffer //////////////////////////////////////////////
	/////////////////////////////////////////////////////////////

	OpenGLVertexBuffer::OpenGLVertexBuffer(uint32_t size)
	{
		ALIEN_RENDER_S1(size, {
			glCreateBuffers(1, &self->m_RendererID);
			glBindBuffer(GL_ARRAY_BUFFER, self->m_RendererID);
			glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
			});
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(float* vertices, uint32_t size)
	{
		m_Buffer.reset(new char[size]);
		memcpy(m_Buffer.get(), vertices, size);

		ALIEN_RENDER_S1(size, {
			glCreateBuffers(1, &self->m_RendererID);
			glBindBuffer(GL_ARRAY_BUFFER, self->m_RendererID);
			glBufferData(GL_ARRAY_BUFFER, size, self->m_Buffer.get(), GL_STATIC_DRAW);
			});

	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		ALIEN_RENDER_S({
			glDeleteBuffers(1, &self->m_RendererID);
			});
	}

	void OpenGLVertexBuffer::Bind() const
	{
		ALIEN_RENDER_S({
			glBindBuffer(GL_ARRAY_BUFFER, self->m_RendererID);
			});
	}

	void OpenGLVertexBuffer::UnBind() const
	{
		ALIEN_RENDER({
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			});
	}

	void OpenGLVertexBuffer::SetData(const void* data, uint32_t size)
	{
		m_Buffer.reset(new char[size]);
		memcpy(m_Buffer.get(), data, size);

		ALIEN_RENDER_S1(size, {
			glBindBuffer(GL_ARRAY_BUFFER, self->m_RendererID);
			glBufferSubData(GL_ARRAY_BUFFER, 0, size, self->m_Buffer.get());
			});
	}

	/////////////////////////////////////////////////////////////
	// IndexBuffer //////////////////////////////////////////////
	/////////////////////////////////////////////////////////////

	OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* indices, uint32_t count)
		: m_Count(count)
	{
		int size = count * sizeof(uint32_t);
		m_Buffer.reset(new char[size]);
		memcpy(m_Buffer.get(), indices, size);

		ALIEN_RENDER_S1(count, {
			glCreateBuffers(1, &self->m_RendererID);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self->m_RendererID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), self->m_Buffer.get(), GL_STATIC_DRAW);
			});

	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		ALIEN_RENDER_S({
			glDeleteBuffers(1, &self->m_RendererID);
			});
	}

	void OpenGLIndexBuffer::Bind() const
	{
		ALIEN_RENDER_S({
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self->m_RendererID);
			});
	}

	void OpenGLIndexBuffer::UnBind() const
	{
		ALIEN_RENDER({
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			});
	}



#if 0
	/////////////////////////////////////////////////////////////
	// VertexBuffer //////////////////////////////////////////////
	/////////////////////////////////////////////////////////////

	OpenGLVertexBuffer::OpenGLVertexBuffer() : m_RendererID(0), m_Size(0)
	{
		ALIEN_RENDER_S({
			glCreateBuffers(1, &self->m_RendererID);
		});
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		ALIEN_RENDER_S({
			glDeleteBuffers(1, &self->m_RendererID);
		});

		/*if (m_Buffer) delete m_Buffer;
		m_Buffer = nullptr;*/
	}

	void OpenGLVertexBuffer::SetData(void* buffer, uint32_t size, uint32_t offset)
	{
		m_Size = size;

		m_Buffer.reset(new char[size]);
		memcpy(m_Buffer.get(), buffer, size);


		ALIEN_RENDER_S2(size, offset, {
			glBindBuffer(GL_ARRAY_BUFFER, self->m_RendererID);
			glBufferData(GL_ARRAY_BUFFER, size, self->m_Buffer.get(), GL_STATIC_DRAW);
		});
	}

	void OpenGLVertexBuffer::Bind() const
	{
		ALIEN_RENDER_S({
			if(self->m_RendererID)
				glBindBuffer(GL_ARRAY_BUFFER, self->m_RendererID);
			else
				ALIEN_CORE_ERROR("OpenGLVertexBuffer m_RendererID is 0;");
		});
	}

	void OpenGLVertexBuffer::UnBind() const
	{
		ALIEN_RENDER({
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		});
	}

	/////////////////////////////////////////////////////////////
	// IndexBuffer //////////////////////////////////////////////
	/////////////////////////////////////////////////////////////

	OpenGLIndexBuffer::OpenGLIndexBuffer() : m_RendererID(0), m_Size(0)
	{
		ALIEN_RENDER_S({
			glCreateBuffers(1, &self->m_RendererID);
		});
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		ALIEN_RENDER_S({
			glDeleteBuffers(1, &self->m_RendererID);
		});

		/*if (m_Buffer) delete m_Buffer;
		m_Buffer = nullptr;*/
	}

	void OpenGLIndexBuffer::SetData(void* buffer, uint32_t size, uint32_t offset)
	{
		m_Size = size;

		m_Buffer.reset(new char[size]);
		memcpy(m_Buffer.get(), buffer, size);

		ALIEN_RENDER_S2(size, offset, {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self->m_RendererID);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, self->m_Buffer.get(), GL_STATIC_DRAW);
		});
	}

	void OpenGLIndexBuffer::Bind() const
	{
		ALIEN_RENDER_S({
			if (self->m_RendererID)
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, self->m_RendererID);
			else
				ALIEN_CORE_ERROR("OpenGLIndexBuffer m_RendererID is 0;");
		});
	}

	void OpenGLIndexBuffer::UnBind() const
	{
		ALIEN_RENDER({
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		});
	}
#endif
}


