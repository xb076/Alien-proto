#include "pch.h"
#include "Alien/Renderer/Renderer2D.h"
#include "Alien/Renderer/Renderer.h"

#include "Alien/Renderer/VertexArray.h"
#include "Alien/Renderer/Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Alien {

	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 TexCoord;
		float TexIndex;
		float TilingFactor;
	};

	struct Renderer2DData
	{
		static const uint32_t MaxQuads = 20000;
		static const uint32_t MaxVertices = MaxQuads * 4;
		static const uint32_t MaxIndices = MaxQuads * 6;
		static const uint32_t MaxTextureSlots = 32; // TODO: RenderCaps

		Ref<VertexArray> QuadVertexArray;
		Ref<VertexBuffer> QuadVertexBuffer;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;

		uint32_t QuadIndexCount = 0;
		QuadVertex* QuadVertexBufferBase = nullptr;
		QuadVertex* QuadVertexBufferPtr = nullptr;

		std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
		uint32_t TextureSlotIndex = 1; // 0 = white texture

		glm::vec4 QuadVertexPositions[4];

		Renderer2D::Statistics Stats;

		//to delete
		Ref<Shader> FlatColorShader;
	};

	static Renderer2DData s_RenderData;

	void Renderer2D::Init()
	{

		//s_RenderData = new Renderer2DData();

		s_RenderData.QuadVertexArray.reset(VertexArray::Create());

		s_RenderData.QuadVertexBuffer = VertexBuffer::Create(s_RenderData.MaxVertices * sizeof(QuadVertex));

		s_RenderData.QuadVertexBuffer->SetLayout({
			{ ShaderDataType::Float3, "a_Position" },
			{ ShaderDataType::Float4, "a_Color" },
			{ ShaderDataType::Float2, "a_TexCoord" },
			{ ShaderDataType::Float, "a_TexIndex" },
			{ ShaderDataType::Float, "a_TilingFactor" }
			});
		s_RenderData.QuadVertexArray->AddVertexBuffer(s_RenderData.QuadVertexBuffer);

		s_RenderData.QuadVertexBufferBase = new QuadVertex[s_RenderData.MaxVertices];

		uint32_t quadIndices[s_RenderData.MaxIndices];
		uint32_t offset = 0;
		for (uint32_t i = 0; i < s_RenderData.MaxIndices; i += 6)
		{
			quadIndices[i + 0] = offset + 0;
			quadIndices[i + 1] = offset + 1;
			quadIndices[i + 2] = offset + 2;
			quadIndices[i + 3] = offset + 2;
			quadIndices[i + 4] = offset + 3;
			quadIndices[i + 5] = offset + 0;

			offset += 4;
		}
		Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, s_RenderData.MaxIndices);
		s_RenderData.QuadVertexArray->SetIndexBuffer(quadIB);

		s_RenderData.WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		s_RenderData.WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		uint32_t samplers[s_RenderData.MaxTextureSlots];
		for (uint32_t i = 0; i < s_RenderData.MaxTextureSlots; ++i)
			samplers[i] = i;

		//s_RenderData.FlatColorShader = Engine::Shader::Create("assets/shaders/FlatColor.glsl");
		s_RenderData.TextureShader = Alien::Shader::Create("assets/shaders/Texture.glsl");
		s_RenderData.TextureShader->Bind();
		s_RenderData.TextureShader->SetIntArray("u_Textures", samplers, s_RenderData.MaxTextureSlots);

		// Set all texture slots to 0
		s_RenderData.TextureSlots[0] = s_RenderData.WhiteTexture;

		s_RenderData.QuadVertexPositions[0] = glm::vec4( -0.5f, -0.5f, 0.0f, 1.0f );
		s_RenderData.QuadVertexPositions[1] = glm::vec4(0.5f, -0.5f, 0.0f, 1.0f );
		s_RenderData.QuadVertexPositions[2] = glm::vec4(0.5f,  0.5f, 0.0f, 1.0f );
		s_RenderData.QuadVertexPositions[3] = glm::vec4(-0.5f,  0.5f, 0.0f, 1.0f );


	}

	void Renderer2D::Shutdown()
	{
		
		delete[] s_RenderData.QuadVertexBufferBase;
	}

	void Renderer2D::BeginScene(const OrthographicCamera& camera)
	{
		
		//s_RenderData.FlatColorShader->Bind();
		//s_RenderData.FlatColorShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

		s_RenderData.TextureShader->Bind();
		s_RenderData.TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

		s_RenderData.QuadIndexCount = 0;
		s_RenderData.QuadVertexBufferPtr = s_RenderData.QuadVertexBufferBase;

		/*s_RenderData.TextureShader->Bind();
		s_RenderData.TextureShader->SetMat4("u_ViewProjection", camera.GetViewProjectionMatrix());

		s_RenderData.QuadIndexCount = 0;
		s_RenderData.QuadVertexBufferPtr = s_RenderData.QuadVertexBufferBase;

		s_RenderData.TextureSlotIndex = 1;*/
	}

	void Renderer2D::EndScene()
	{
		
		uint32_t dataSize = (uint32_t)((uint8_t*)s_RenderData.QuadVertexBufferPtr - (uint8_t*)s_RenderData.QuadVertexBufferBase);
		s_RenderData.QuadVertexBuffer->SetData(s_RenderData.QuadVertexBufferBase, dataSize);

		Flush();
	}

	void Renderer2D::Flush()
	{

		for (uint32_t i = 0; i < s_RenderData.TextureSlotIndex; i++)
			s_RenderData.TextureSlots[i]->Bind(i);
		//
		Renderer::DrawIndexed(s_RenderData.QuadVertexArray, s_RenderData.QuadIndexCount);
		s_RenderData.Stats.DrawCalls++;

	}

	void Renderer2D::FlushAndReset()
	{
		EndScene();

		s_RenderData.QuadIndexCount = 0;
		s_RenderData.QuadVertexBufferPtr = s_RenderData.QuadVertexBufferBase;

		s_RenderData.TextureSlotIndex = 1;
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
	{
		DrawQuad(glm::vec3( position.x, position.y, 0.f ), size, color);

	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
	{

		if (s_RenderData.QuadIndexCount >= Renderer2DData::MaxIndices)
			FlushAndReset();

		const float texIndex = 0.f; //white texture
		const float tilingFactor = 1.f;

		glm::mat4 transform = glm::translate(glm::mat4(1.f), position)
			* glm::scale(glm::mat4(1.0f), glm::vec3( size.x, size.y, 1.f ));

		s_RenderData.QuadVertexBufferPtr->Position = glm::vec3(transform * s_RenderData.QuadVertexPositions[0]);
		s_RenderData.QuadVertexBufferPtr->Color = color;
		s_RenderData.QuadVertexBufferPtr->TexCoord = glm::vec2( 0.f,0.f );
		s_RenderData.QuadVertexBufferPtr->TexIndex = texIndex;
		s_RenderData.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_RenderData.QuadVertexBufferPtr++;

		s_RenderData.QuadVertexBufferPtr->Position = glm::vec3(transform * s_RenderData.QuadVertexPositions[1]);
		s_RenderData.QuadVertexBufferPtr->Color = color;
		s_RenderData.QuadVertexBufferPtr->TexCoord = glm::vec2(1.f, 0.f);
		s_RenderData.QuadVertexBufferPtr->TexIndex = texIndex;
		s_RenderData.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_RenderData.QuadVertexBufferPtr++;

		s_RenderData.QuadVertexBufferPtr->Position = glm::vec3(transform * s_RenderData.QuadVertexPositions[2]);
		s_RenderData.QuadVertexBufferPtr->Color = color;
		s_RenderData.QuadVertexBufferPtr->TexCoord = glm::vec2(1.f, 1.f);
		s_RenderData.QuadVertexBufferPtr->TexIndex = texIndex;
		s_RenderData.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_RenderData.QuadVertexBufferPtr++;

		s_RenderData.QuadVertexBufferPtr->Position = glm::vec3(transform * s_RenderData.QuadVertexPositions[3]);
		s_RenderData.QuadVertexBufferPtr->Color = color;
		s_RenderData.QuadVertexBufferPtr->TexCoord = glm::vec2(0.f, 1.f);
		s_RenderData.QuadVertexBufferPtr->TexIndex = texIndex;
		s_RenderData.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_RenderData.QuadVertexBufferPtr++;

		s_RenderData.QuadIndexCount += 6;

		s_RenderData.Stats.QuadCount++;
	}

	void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		DrawQuad(glm::vec3( position.x, position.y, 0.0f ), size, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{

		if (s_RenderData.QuadIndexCount >= Renderer2DData::MaxIndices)
			FlushAndReset();

		glm::vec4 color = glm::vec4( 1.f, 1.f, 1.f, 1.f );

		uint32_t textureIndex = 0.0f;

		for (uint32_t i = 1; i < s_RenderData.TextureSlotIndex; i++)
		{
			if (*s_RenderData.TextureSlots[i].get() == *texture.get())
			{
				textureIndex = i;
				break;
			}
		}

		if (0 == textureIndex)
		{
			textureIndex = s_RenderData.TextureSlotIndex;
			s_RenderData.TextureSlots[s_RenderData.TextureSlotIndex] = texture;
			s_RenderData.TextureSlotIndex++;
		}

		glm::mat4 transform = glm::translate(glm::mat4(1.f), position)
			* glm::scale(glm::mat4(1.0f), glm::vec3( size.x, size.y, 1.f ));


		s_RenderData.QuadVertexBufferPtr->Position = glm::vec3(transform * s_RenderData.QuadVertexPositions[0]);
		s_RenderData.QuadVertexBufferPtr->Color = color;
		s_RenderData.QuadVertexBufferPtr->TexCoord = glm::vec2( 0.f,0.f );
		s_RenderData.QuadVertexBufferPtr->TexIndex = (float)textureIndex;
		s_RenderData.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_RenderData.QuadVertexBufferPtr++;

		s_RenderData.QuadVertexBufferPtr->Position = glm::vec3(transform * s_RenderData.QuadVertexPositions[1]);
		s_RenderData.QuadVertexBufferPtr->Color = color;
		s_RenderData.QuadVertexBufferPtr->TexCoord = glm::vec2(1.f, 0.f);
		s_RenderData.QuadVertexBufferPtr->TexIndex = (float)textureIndex;
		s_RenderData.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_RenderData.QuadVertexBufferPtr++;

		s_RenderData.QuadVertexBufferPtr->Position = glm::vec3(transform * s_RenderData.QuadVertexPositions[2]);
		s_RenderData.QuadVertexBufferPtr->Color = color;
		s_RenderData.QuadVertexBufferPtr->TexCoord = glm::vec2(1.f, 1.f);
		s_RenderData.QuadVertexBufferPtr->TexIndex = (float)textureIndex;
		s_RenderData.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_RenderData.QuadVertexBufferPtr++;

		s_RenderData.QuadVertexBufferPtr->Position = glm::vec3(transform * s_RenderData.QuadVertexPositions[3]);
		s_RenderData.QuadVertexBufferPtr->Color = color;
		s_RenderData.QuadVertexBufferPtr->TexCoord = glm::vec2(0.f, 1.f);
		s_RenderData.QuadVertexBufferPtr->TexIndex = (float)textureIndex;
		s_RenderData.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_RenderData.QuadVertexBufferPtr++;

		s_RenderData.QuadIndexCount += 6;

		s_RenderData.Stats.QuadCount++;
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{
		DrawRotatedQuad(glm::vec3( position.x, position.y, 0.0f ), size, rotation, color);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
	{

		const float texIndex = 0.f; //white texture
		const float tilingFactor = 1.f;

		glm::mat4 transform = glm::translate(glm::mat4(1.f), position)
			* glm::rotate(glm::mat4(1.0f), rotation, glm::vec3( 0.f,0.f,1.f ))
			* glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.f ));


		s_RenderData.QuadVertexBufferPtr->Position = glm::vec3(transform * s_RenderData.QuadVertexPositions[0]);
		s_RenderData.QuadVertexBufferPtr->Color = color;
		s_RenderData.QuadVertexBufferPtr->TexCoord = glm::vec2(0.f, 0.f);
		s_RenderData.QuadVertexBufferPtr->TexIndex = texIndex;
		s_RenderData.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_RenderData.QuadVertexBufferPtr++;

		s_RenderData.QuadVertexBufferPtr->Position = glm::vec3(transform * s_RenderData.QuadVertexPositions[1]);
		s_RenderData.QuadVertexBufferPtr->Color = color;
		s_RenderData.QuadVertexBufferPtr->TexCoord = glm::vec2(1.f, 0.f);
		s_RenderData.QuadVertexBufferPtr->TexIndex = texIndex;
		s_RenderData.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_RenderData.QuadVertexBufferPtr++;

		s_RenderData.QuadVertexBufferPtr->Position = glm::vec3(transform * s_RenderData.QuadVertexPositions[2]);
		s_RenderData.QuadVertexBufferPtr->Color = color;
		s_RenderData.QuadVertexBufferPtr->TexCoord = glm::vec2(1.f, 1.f);
		s_RenderData.QuadVertexBufferPtr->TexIndex = texIndex;
		s_RenderData.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_RenderData.QuadVertexBufferPtr++;

		s_RenderData.QuadVertexBufferPtr->Position = glm::vec3(transform * s_RenderData.QuadVertexPositions[3]);
		s_RenderData.QuadVertexBufferPtr->Color = color;
		s_RenderData.QuadVertexBufferPtr->TexCoord = glm::vec2(0.f, 1.f);
		s_RenderData.QuadVertexBufferPtr->TexIndex = texIndex;
		s_RenderData.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_RenderData.QuadVertexBufferPtr++;

		s_RenderData.QuadIndexCount += 6;

		s_RenderData.Stats.QuadCount++;
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{
		DrawRotatedQuad(glm::vec3( position.x, position.y, 0.0f), size, rotation, texture, tilingFactor, tintColor);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
	{

		glm::vec4 color = glm::vec4(1.f, 1.f, 1.f, 1.f );

		uint32_t textureIndex = 0;

		for (uint32_t i = 1; i < s_RenderData.TextureSlotIndex; i++)
		{
			if (*s_RenderData.TextureSlots[i].get() == *texture.get())
			{
				textureIndex = i;
				break;
			}
		}

		if (0 == textureIndex)
		{
			textureIndex = s_RenderData.TextureSlotIndex;
			s_RenderData.TextureSlots[s_RenderData.TextureSlotIndex] = texture;
			s_RenderData.TextureSlotIndex++;
		}

		glm::mat4 transform = glm::translate(glm::mat4(1.f), position)
			* glm::rotate(glm::mat4(1.0f), rotation, glm::vec3( 0.f,0.f,1.f ))
			* glm::scale(glm::mat4(1.0f), glm::vec3(size.x, size.y, 1.f ));

		s_RenderData.QuadVertexBufferPtr->Position = glm::vec3(transform * s_RenderData.QuadVertexPositions[0]);
		s_RenderData.QuadVertexBufferPtr->Color = color;
		s_RenderData.QuadVertexBufferPtr->TexCoord = glm::vec2(0.f, 0.f);
		s_RenderData.QuadVertexBufferPtr->TexIndex = (float)textureIndex;
		s_RenderData.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_RenderData.QuadVertexBufferPtr++;

		s_RenderData.QuadVertexBufferPtr->Position = glm::vec3(transform * s_RenderData.QuadVertexPositions[1]);
		s_RenderData.QuadVertexBufferPtr->Color = color;
		s_RenderData.QuadVertexBufferPtr->TexCoord = glm::vec2(1.f, 0.f);
		s_RenderData.QuadVertexBufferPtr->TexIndex = (float)textureIndex;
		s_RenderData.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_RenderData.QuadVertexBufferPtr++;

		s_RenderData.QuadVertexBufferPtr->Position = glm::vec3(transform * s_RenderData.QuadVertexPositions[2]);
		s_RenderData.QuadVertexBufferPtr->Color = color;
		s_RenderData.QuadVertexBufferPtr->TexCoord = glm::vec2(1.f, 1.f);
		s_RenderData.QuadVertexBufferPtr->TexIndex = (float)textureIndex;
		s_RenderData.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_RenderData.QuadVertexBufferPtr++;

		s_RenderData.QuadVertexBufferPtr->Position = glm::vec3(transform * s_RenderData.QuadVertexPositions[3]);
		s_RenderData.QuadVertexBufferPtr->Color = color;
		s_RenderData.QuadVertexBufferPtr->TexCoord = glm::vec2(0.f, 1.f);
		s_RenderData.QuadVertexBufferPtr->TexIndex = (float)textureIndex;
		s_RenderData.QuadVertexBufferPtr->TilingFactor = tilingFactor;
		s_RenderData.QuadVertexBufferPtr++;

		s_RenderData.QuadIndexCount += 6;

		s_RenderData.Stats.QuadCount++;

	}

	void Renderer2D::ResetStats()
	{
		memset(&s_RenderData.Stats, 0, sizeof(Statistics));
	}

	Renderer2D::Statistics Renderer2D::GetStats()
	{
		return s_RenderData.Stats;
	}

}




