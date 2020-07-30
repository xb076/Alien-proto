#pragma once
#include "RenderCommand.h"

namespace Alien {

	class Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(const Ref<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};


}


#define ALIEN_RENDER_PASTE2(a, b) a ## b
#define ALIEN_RENDER_PASTE(a, b) ALIEN_RENDER_PASTE2(a, b)
#define ALIEN_RENDER_UNIQUE(x) ALIEN_RENDER_PASTE(x, __LINE__)

#define ALIEN_RENDER(code) \
    struct ALIEN_RENDER_UNIQUE(AlienRenderCommand) \
    {\
        static void Execute(void*)\
        {\
            code\
        }\
    };\
	{\
		auto mem = ::Alien::Renderer::Submit(ALIEN_RENDER_UNIQUE(AlienRenderCommand)::Execute, sizeof(ALIEN_RENDER_UNIQUE(AlienRenderCommand)));\
		new (mem) ALIEN_RENDER_UNIQUE(AlienRenderCommand)();\
	}\

#define ALIEN_RENDER_1(arg0, code) \
	do {\
    struct ALIEN_RENDER_UNIQUE(AlienRenderCommand) \
    {\
		ALIEN_RENDER_UNIQUE(AlienRenderCommand)(typename ::std::remove_const<typename ::std::remove_reference<decltype(arg0)>::type>::type arg0) \
		: arg0(arg0) {}\
		\
        static void Execute(void* argBuffer)\
        {\
			auto& arg0 = ((ALIEN_RENDER_UNIQUE(AlienRenderCommand)*)argBuffer)->arg0;\
            code\
        }\
		\
		typename ::std::remove_const<typename ::std::remove_reference<decltype(arg0)>::type>::type arg0;\
    };\
	{\
		auto mem = ::Alien::Renderer::Submit(ALIEN_RENDER_UNIQUE(AlienRenderCommand)::Execute, sizeof(ALIEN_RENDER_UNIQUE(AlienRenderCommand)));\
		new (mem) ALIEN_RENDER_UNIQUE(AlienRenderCommand)(arg0);\
	} } while(0)

#define ALIEN_RENDER_2(arg0, arg1, code) \
    struct ALIEN_RENDER_UNIQUE(AlienRenderCommand) \
    {\
		ALIEN_RENDER_UNIQUE(AlienRenderCommand)(typename ::std::remove_const<typename ::std::remove_reference<decltype(arg0)>::type>::type arg0,\
											typename ::std::remove_const<typename ::std::remove_reference<decltype(arg1)>::type>::type arg1) \
		: arg0(arg0), arg1(arg1) {}\
		\
        static void Execute(void* argBuffer)\
        {\
			auto& arg0 = ((ALIEN_RENDER_UNIQUE(AlienRenderCommand)*)argBuffer)->arg0;\
			auto& arg1 = ((ALIEN_RENDER_UNIQUE(AlienRenderCommand)*)argBuffer)->arg1;\
            code\
        }\
		\
		typename ::std::remove_const<typename ::std::remove_reference<decltype(arg0)>::type>::type arg0;\
		typename ::std::remove_const<typename ::std::remove_reference<decltype(arg1)>::type>::type arg1;\
    };\
	{\
		auto mem = ::Alien::Renderer::Submit(ALIEN_RENDER_UNIQUE(AlienRenderCommand)::Execute, sizeof(ALIEN_RENDER_UNIQUE(AlienRenderCommand)));\
		new (mem) ALIEN_RENDER_UNIQUE(AlienRenderCommand)(arg0, arg1);\
	}\

#define ALIEN_RENDER_3(arg0, arg1, arg2, code) \
    struct ALIEN_RENDER_UNIQUE(AlienRenderCommand) \
    {\
		ALIEN_RENDER_UNIQUE(AlienRenderCommand)(typename ::std::remove_const<typename ::std::remove_reference<decltype(arg0)>::type>::type arg0,\
											typename ::std::remove_const<typename ::std::remove_reference<decltype(arg1)>::type>::type arg1,\
											typename ::std::remove_const<typename ::std::remove_reference<decltype(arg2)>::type>::type arg2) \
		: arg0(arg0), arg1(arg1), arg2(arg2) {}\
		\
        static void Execute(void* argBuffer)\
        {\
			auto& arg0 = ((ALIEN_RENDER_UNIQUE(AlienRenderCommand)*)argBuffer)->arg0;\
			auto& arg1 = ((ALIEN_RENDER_UNIQUE(AlienRenderCommand)*)argBuffer)->arg1;\
			auto& arg2 = ((ALIEN_RENDER_UNIQUE(AlienRenderCommand)*)argBuffer)->arg2;\
            code\
        }\
		\
		typename ::std::remove_const<typename ::std::remove_reference<decltype(arg0)>::type>::type arg0;\
		typename ::std::remove_const<typename ::std::remove_reference<decltype(arg1)>::type>::type arg1;\
		typename ::std::remove_const<typename ::std::remove_reference<decltype(arg2)>::type>::type arg2;\
    };\
	{\
		auto mem = ::Alien::Renderer::Submit(ALIEN_RENDER_UNIQUE(AlienRenderCommand)::Execute, sizeof(ALIEN_RENDER_UNIQUE(AlienRenderCommand)));\
		new (mem) ALIEN_RENDER_UNIQUE(AlienRenderCommand)(arg0, arg1, arg2);\
	}\

#define ALIEN_RENDER_4(arg0, arg1, arg2, arg3, code) \
    struct ALIEN_RENDER_UNIQUE(AlienRenderCommand) \
    {\
		ALIEN_RENDER_UNIQUE(AlienRenderCommand)(typename ::std::remove_const<typename ::std::remove_reference<decltype(arg0)>::type>::type arg0,\
											typename ::std::remove_const<typename ::std::remove_reference<decltype(arg1)>::type>::type arg1,\
											typename ::std::remove_const<typename ::std::remove_reference<decltype(arg2)>::type>::type arg2,\
											typename ::std::remove_const<typename ::std::remove_reference<decltype(arg3)>::type>::type arg3)\
		: arg0(arg0), arg1(arg1), arg2(arg2), arg3(arg3) {}\
		\
        static void Execute(void* argBuffer)\
        {\
			auto& arg0 = ((ALIEN_RENDER_UNIQUE(AlienRenderCommand)*)argBuffer)->arg0;\
			auto& arg1 = ((ALIEN_RENDER_UNIQUE(AlienRenderCommand)*)argBuffer)->arg1;\
			auto& arg2 = ((ALIEN_RENDER_UNIQUE(AlienRenderCommand)*)argBuffer)->arg2;\
			auto& arg3 = ((ALIEN_RENDER_UNIQUE(AlienRenderCommand)*)argBuffer)->arg3;\
            code\
        }\
		\
		typename ::std::remove_const<typename ::std::remove_reference<decltype(arg0)>::type>::type arg0;\
		typename ::std::remove_const<typename ::std::remove_reference<decltype(arg1)>::type>::type arg1;\
		typename ::std::remove_const<typename ::std::remove_reference<decltype(arg2)>::type>::type arg2;\
		typename ::std::remove_const<typename ::std::remove_reference<decltype(arg3)>::type>::type arg3;\
    };\
	{\
		auto mem = Renderer::Submit(ALIEN_RENDER_UNIQUE(AlienRenderCommand)::Execute, sizeof(ALIEN_RENDER_UNIQUE(AlienRenderCommand)));\
		new (mem) ALIEN_RENDER_UNIQUE(AlienRenderCommand)(arg0, arg1, arg2, arg3);\
	}

#define ALIEN_RENDER_S(code) auto self = this;\
	ALIEN_RENDER_1(self, code)

#define ALIEN_RENDER_S1(arg0, code) auto self = this;\
	ALIEN_RENDER_2(self, arg0, code)

#define ALIEN_RENDER_S2(arg0, arg1, code) auto self = this;\
	ALIEN_RENDER_3(self, arg0, arg1, code)

#define ALIEN_RENDER_S3(arg0, arg1, arg2, code) auto self = this;\
	ALIEN_RENDER_4(self, arg0, arg1, arg2, code)



