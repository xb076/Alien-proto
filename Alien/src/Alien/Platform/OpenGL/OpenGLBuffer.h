#pragma once
#include "Alien/Renderer/Buffer.h"

namespace Alien {

	/////////////////////////////////////////////////////////////
	// VertexBuffer //////////////////////////////////////////////
	/////////////////////////////////////////////////////////////

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(uint32_t size);
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual const BufferLayout& GetLayout() const override { return m_Layout; }
		virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; };
		virtual void SetData(const void* data, uint32_t size) override;

	private:
		uint32_t m_RendererID;
		BufferLayout m_Layout;

	};

	/////////////////////////////////////////////////////////////
	// IndexBuffer //////////////////////////////////////////////
	/////////////////////////////////////////////////////////////

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() const override;
		virtual void UnBind() const override;
		virtual uint32_t GetCount() const override { return m_Count; }

	private:
		uint32_t m_RendererID;
		uint32_t m_Count;

	};
#if 0
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
#endif
	
}

