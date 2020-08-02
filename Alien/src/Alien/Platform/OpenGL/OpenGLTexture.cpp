#include "pch.h"
#include "OpenGLTexture.h"
#include "stb_image.h"
#include <glad/glad.h>
#include "Alien/Renderer/Renderer.h"

namespace Alien {

	OpenGLTexture2D::OpenGLTexture2D(uint32_t width, uint32_t height)
		: m_Width(width), m_Height(height), m_ImageData(0)
	{
		
		m_InternalFormat = GL_RGBA8;
		m_DataFormat = GL_RGBA;

		ALIEN_RENDER_S({
			glCreateTextures(GL_TEXTURE_2D, 1, &self->m_RendererID);
			glTextureStorage2D(self->m_RendererID, 1, self->m_InternalFormat, self->m_Width, self->m_Height);

			glTextureParameteri(self->m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTextureParameteri(self->m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glTextureParameteri(self->m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTextureParameteri(self->m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
		});
	}

	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		: m_Path(path), m_ImageData(0)
	{
		
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);

		//stbi_uc* data = nullptr;
		{
			//ENGINE_PROFILE_SCOPE("stbi_load() OpenGLTexture2D::OpenGLTexture2D(const std::string&)");

			m_ImageData.reset( stbi_load(path.c_str(), &width, &height, &channels, 0));
		}
		ALIEN_CORE_ASSERT(m_ImageData.get(), "Failed to load image!");

		m_Width = width;
		m_Height = height;
		
		GLenum internalFormat = 0, dataFormat = 0;

		if (channels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		m_InternalFormat = internalFormat;
		m_DataFormat = dataFormat;

		/*uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;
		uint32_t size = m_Width * m_Height * bpp;
		m_ImageData.reset(new unsigned char[size]);
		memcpy(m_ImageData.get(), data, size);
		stbi_image_free(data);*/

		ALIEN_CORE_ASSERT(internalFormat && dataFormat, "Format not supported");

		ALIEN_RENDER_S({
			glCreateTextures(GL_TEXTURE_2D, 1, &self->m_RendererID);
			glTextureStorage2D(self->m_RendererID, 1, self->m_InternalFormat, self->m_Width, self->m_Height);

			glTextureParameteri(self->m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTextureParameteri(self->m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

			glTextureParameteri(self->m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTextureParameteri(self->m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

			glTextureSubImage2D(self->m_RendererID, 0, 0, 0, self->m_Width, self->m_Height, self->m_DataFormat, GL_UNSIGNED_BYTE, self->m_ImageData.get());
			
			});
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		ALIEN_RENDER_S({
			glDeleteTextures(1, &self->m_RendererID);
			});

		//if (m_ImageData) delete m_ImageData;
		//m_ImageData = nullptr;
	}

	void OpenGLTexture2D::SetData(void* data, uint32_t size)
	{
		uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;
		ALIEN_CORE_ASSERT(size == m_Width * m_Height * bpp, "Data must be entire texture!");

		m_ImageData.reset(new unsigned char[size]);
		memcpy(m_ImageData.get(), data, size);
		ALIEN_RENDER_S({
			glTextureSubImage2D(self->m_RendererID, 0, 0, 0, self->m_Width, self->m_Height, self->m_DataFormat, GL_UNSIGNED_BYTE, self->m_ImageData.get());
			});
	}

	void OpenGLTexture2D::Bind(uint32_t slot /* = 0 */) const
	{
		ALIEN_RENDER_S1(slot, {
			glBindTextureUnit(slot, self->m_RendererID);
			});
	}

}



