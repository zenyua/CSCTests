#pragma once
#include <string>
#include "SDL2-2.28.0/include/SDL.h"

namespace ringo {
	class Renderer {
	public:
		Renderer() = default;
		~Renderer() = default;

		bool Initialize();
		void Shutdown();
		//my test code
		//void Pause();

		void CreateWindow(const std::string& title, int width, int height);
		void BeginFrame();
		void EndFrame();

		void SetColor(int r, int g, int b, int a);
		void DrawLine(int x1, int y1, int x2, int y2);
		friend class Text;
	private:
		int m_width = 0;
		int m_height = 0;

		SDL_Renderer* m_renderer{ nullptr };
		//added as test
		SDL_Window* m_window{ nullptr };
	};
}