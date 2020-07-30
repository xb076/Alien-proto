#include "pch.h"
#include "OpenGLVertexArray.h"

#include <glad/glad.h>

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

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::UnBind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		ALIEN_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");
		
		glBindVertexArray(m_RendererID);
		vertexBuffer->Bind();


		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
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

		m_VertexBuffers.push_back(vertexBuffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		glBindVertexArray(m_RendererID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

}

