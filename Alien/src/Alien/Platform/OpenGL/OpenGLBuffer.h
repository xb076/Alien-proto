#pragma once
#include "Alien/Renderer/Buffer.h"

namespace Alien {

	/////////////////////////////////////////////////////////////
	// VertexBuffer //////////////////////////////////////////////
	/////////////////////////////////////////////////////////////

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer();
		virtual ~OpenGLVertexBuffer();

		virtual void SetData(void* buffer, uint32_t size, uint32_t offset = 0) override;
		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual const BufferLayout& GetLayout() const override { return m_Layout; }
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; };

		virtual unsigned int GetSize() const { return m_Size; }
		virtual uint32_t GetRendererID() const { return m_RendererID; }

	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;
		unsigned int m_Size;

	};

	/////////////////////////////////////////////////////////////
	// IndexBuffer //////////////////////////////////////////////
	/////////////////////////////////////////////////////////////

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer();
		virtual ~OpenGLIndexBuffer();

		virtual void SetData(void* buffer, uint32_t size, uint32_t offset = 0) override;
		virtual void Bind() const override;
		virtual void UnBind() const override;
		virtual uint32_t GetCount() const override { return m_Size / sizeof(uint32_t); }

		virtual unsigned int GetSize() const { return m_Size; }
		virtual uint32_t GetRendererID() const { return m_RendererID; }

	private:
		uint32_t m_RendererID;
		uint32_t m_Size;

	};

}

