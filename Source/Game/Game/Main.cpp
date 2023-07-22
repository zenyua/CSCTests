#include "Core/Core.h"

#include "Renderer/Renderer.h"
#include "Renderer/Model.h"

#include "Input/InputSystem.h"

#include "Audio/AudioSystem.h"

#include <iostream>
#include <vector>
#include <SDL2-2.28.0/include/SDL.h>

using vec2 = ringo::Vector2;

int main(int argc, char* argv[]) {
	//set up memory
	ringo::MemoryTracker::Initialize();

	//set file path
	ringo::setFilePath("assets");

	//set up audio
	ringo::g_audioSystem.Initialize();
	ringo::g_audioSystem.AddAudio("meow", "meow.wav");
	ringo::g_audioSystem.AddAudio("laser", "laser.wav");

	//set up models
	ringo::Model model;
	std::cout << ringo::getFilePath();
	model.Load("cat.txt");

	//set up renderer
	ringo::Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("CSC196", 800, 600);

	//set up input
	ringo::g_inputSystem.Initialize();

	bool quit = false;
	while (!quit) {
		ringo::g_inputSystem.Update();
		if (ringo::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE)) {
			quit = true;
		}

		ringo::g_audioSystem.Update();
		if (ringo::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE)) {
			ringo::g_audioSystem.PlayOneShot("meow");
			ringo::g_audioSystem.PlayOneShot("laser");
		}

		if (ringo::g_inputSystem.GetMouseButtonDown(0) && !ringo::g_inputSystem.GetMousePrevButtonDown(0)) {
			std::cout << "Left down.\n";
			std::cout << "x: " << ringo::g_inputSystem.GetMousePosition().x;
			std::cout << " y: " << ringo::g_inputSystem.GetMousePosition().y;
			std::cout << "\n";
		}
		if (ringo::g_inputSystem.GetMouseButtonDown(1) && !ringo::g_inputSystem.GetMousePrevButtonDown(1)) {
			std::cout << "Middle down.\n";
			std::cout << "x: " << ringo::g_inputSystem.GetMousePosition().x;
			std::cout << " y: " << ringo::g_inputSystem.GetMousePosition().y;
			std::cout << "\n";
		}
		if (ringo::g_inputSystem.GetMouseButtonDown(2) && !ringo::g_inputSystem.GetMousePrevButtonDown(2)) {
			std::cout << "Right down.\n";
			std::cout << "x: " << ringo::g_inputSystem.GetMousePosition().x;
			std::cout << " y: " << ringo::g_inputSystem.GetMousePosition().y;
			std::cout << "\n";
		}

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

		model.Draw(renderer, { 500,500 }, 0, 10);

		renderer.EndFrame();
	};

	ringo::MemoryTracker::DisplayInfo();

	return 0;
}
