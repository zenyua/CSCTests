#include "Renderer/Renderer.h"
#include "Core/Core.h"
#include <iostream>
#include <SDL2-2.28.0/include/SDL.h>
//using namespace std;

int main(int argc, char** argv) {
	ringo::Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("CSC196", 800, 600);


	while (true) {
		//my test loop
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				return 0;
			}
		}
		renderer.SetColor(0, 0, 0, 0);
		renderer.BeginFrame();
		renderer.SetColor(255, 255, 255, 255);
		renderer.DrawLine(10, 10, 500, 500);
		renderer.DrawLine(300, 300, 400, 400);
		renderer.DrawLine(50, 500, 50, 400);
		renderer.DrawLine(79, 167, 274, 412);
		renderer.EndFrame();
		//std::cin.get();
		//testing std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	return 0;
}