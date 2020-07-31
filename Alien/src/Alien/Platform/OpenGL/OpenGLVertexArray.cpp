#include "pch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>
#include "Alien/Renderer/Renderer.h"

namespace Alien {

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		GLenum ret = 0;
		switch (type)
		{
			case Alien::ShaderDataType::Float:			ret = GL_FLOAT; break;
			case Alien::ShaderDataType::Float2:		ret = GL_FLOAT; break;
			case Alien::ShaderDataType::Float3:		ret = GL_FLOAT; break;
			case Alien::ShaderDataType::Float4:		ret = GL_FLOAT; break;
			case Alien::ShaderDataType::Mat3:			ret = GL_FLOAT; break;
			case Alien::ShaderDataType::Mat4:			ret = GL_FLOAT; break;
			case Alien::ShaderDataType::Int2:			ret = GL_INT; break;
			case Alien::ShaderDataType::Int3:			ret = GL_INT; break;
			case Alien::ShaderDataType::Int4:			ret = GL_INT; break;
			case Alien::ShaderDataType::Bool:			ret = GL_INT; break;
			default: ALIEN_CORE_ASSERT(false, "Unknown ShaderDataType!"); break;
		}
		return ret;
	}

	OpenGLVertexArray::OpenGLVertexArray() : m_RendererID(0)
	{
		ALIEN_RENDER_S({
			glCreateVertexArrays(1, &self->m_RendererID);
			ALIEN_CORE_INFO("OpenGLVertexArray() m_RendererID<{0}>", self->m_RendererID);
		});
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		ALIEN_RENDER_S({
			ALIEN_CORE_INFO("~OpenGLVertexArray() m_RendererID<{0}>", self->m_RendererID);
			glDeleteVertexArrays(1, &self->m_RendererID);
		});
	}

	void OpenGLVertexArray::Bind() const
	{
		ALIEN_RENDER_S({
			ALIEN_CORE_INFO("OpenGLVertexArray::Bind() m_RendererID<{0}>", self->m_RendererID);
			if(self->m_RendererID)
				glBindVertexArray(self->m_RendererID);
			else
				ALIEN_CORE_ERROR("OpenGLVertexArray m_RendererID is 0;");
		});
	}

	void OpenGLVertexArray::UnBind() const
	{
		ALIEN_RENDER({
			ALIEN_CORE_INFO("OpenGLVertexArray::UnBind()");
			glBindVertexArray(0);
		});
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		ALIEN_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");
		
		Bind();
		vertexBuffer->Bind();

		ALIEN_RENDER_1(vertexBuffer, {
		ALIEN_CORE_INFO("OpenGLVertexArray::AddVertexBuffer()");
		uint32_t index = 0;
		const auto & layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(index
				, element.GetComponentCount()
				, ShaderDataTypeToOpenGLBaseType(element.Type)
				, element.Normalized ? GL_TRUE : GL_FALSE
				, layout.GetStride()
				, (const void*)element.Offset
			);
			++index;
		}
		});

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		Bind();
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

}

