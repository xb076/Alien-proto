#pragma once

#include <glm/glm.hpp>
#include "VertexArray.h"

namespace Alien {

	class RendererAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1
		};

		struct RenderAPICapabilities
		{
			std::string Vendor;
			std::string Renderer;
			std::string Version;

			int MaxSamples;
			float MaxAnisotropy;
		};

	public:
		virtual void Init() = 0;
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		//virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;
		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) = 0;

		virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;

		static RenderAPICapabilities& GetCapabilities()
		{
			static RenderAPICapabilities capabilities;
			return capabilities;
		}

		inline static API GetAPI() { return s_API; }

		static RendererAPI* Create();
	private:
		static API s_API;
	};

}

