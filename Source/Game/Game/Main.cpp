#include "Core/Core.h"

#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include "Renderer/Font.h"
#include "Renderer/Text.h"

#include "Input/Inputsystem.h"

#include "Audio/Audiosystem.h"

#include <iostream>
#include <vector>

using vec2 = ringo::Vector2;

int main(int argc, char* argv[]) {
	//set up memory
	ringo::MemoryTracker::Initialize();
	ringo::MemoryTracker::DisplayInfo();

	//set file path
	ringo::setFilePath("assets");

	//set up audio
	ringo::g_audioSystem.Initialize();
	ringo::g_audioSystem.AddAudio("meow", "meow.wav");
	ringo::g_audioSystem.AddAudio("laser", "laser.wav");

	//set up models
	ringo::Model model;
	std::cout << ringo::getFilePath() << std::endl;
	model.Load("cat.txt");

	//set up renderer
	ringo::Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("csc196", 800, 600);

	//set up input
	ringo::g_inputSystem.Initialize();

	//set up text
	std::shared_ptr<ringo::Font> font = std::make_shared<ringo::Font>("organo.ttf", 48);
	std::unique_ptr<ringo::Text> text = std::make_unique<ringo::Text>(font);
	text->Create(renderer, "mewmont", ringo::Color{1,1,1,1});

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
			std::cout << "left down.\n";
			std::cout << "x: " << ringo::g_inputSystem.GetMousePosition().x;
			std::cout << " y: " << ringo::g_inputSystem.GetMousePosition().y;
			std::cout << "\n";
		}
		if (ringo::g_inputSystem.GetMouseButtonDown(1) && !ringo::g_inputSystem.GetMousePrevButtonDown(1)) {
			std::cout << "middle down.\n";
			std::cout << "x: " << ringo::g_inputSystem.GetMousePosition().x;
			std::cout << " y: " << ringo::g_inputSystem.GetMousePosition().y;
			std::cout << "\n";
		}
		if (ringo::g_inputSystem.GetMouseButtonDown(2) && !ringo::g_inputSystem.GetMousePrevButtonDown(2)) {
			std::cout << "right down.\n";
			std::cout << "x: " << ringo::g_inputSystem.GetMousePosition().x;
			std::cout << " y: " << ringo::g_inputSystem.GetMousePosition().y;
			std::cout << "\n";
		}


		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				return 0;
			}
		}

		renderer.SetColor(255, 255, 255, 0);
		renderer.BeginFrame();
		renderer.SetColor(1, 1, 1, 255);


		model.Draw(renderer, { 500,500 }, 0, 10);

		renderer.SetColor(1, 1, 1, 255);
		text->Draw(renderer, 500, 500);
		//text->draw(renderer, 0, 300);
		//text->draw(renderer, 300, 0);

		renderer.EndFrame();
	};

	ringo::MemoryTracker::DisplayInfo();

	return 0;
}
