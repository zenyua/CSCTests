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
	ringo::Transform transform;
	transform.position = {400, 400};
	int speed = 5;

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
		//time stuff
		ringo::g_time.Tick();
		//inputSystem stuff
		ringo::g_inputSystem.Update();
		//check if ending game
		if (ringo::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE)) {
			quit = true;
		}
		//audio system stuff
		ringo::g_audioSystem.Update();
		if (ringo::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE)) {
			ringo::g_audioSystem.PlayOneShot("meow");
			ringo::g_audioSystem.PlayOneShot("laser");
		}
		//player movement stuff
		ringo::vec2 direction{0, 0};
		if (ringo::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) direction.y = -1;
		if (ringo::g_inputSystem.GetKeyDown(SDL_SCANCODE_S)) direction.y = 1;
		if (ringo::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) direction.x = -1;
		if (ringo::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) direction.x = 1;
		direction = direction * speed * ringo::g_time.GetDeltaTime();
		transform.position = transform.position + direction;

		//SDL_Event loop
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				return 0;
			}
		}

		//renderer setup
		renderer.SetColor(255, 255, 255, 0);
		renderer.BeginFrame();
		renderer.SetColor(1, 1, 1, 255);

		//draw objects
		model.Draw(renderer, transform.position, 0, 10);
		text->Draw(renderer, 500, 500);

		renderer.EndFrame();
	};

	ringo::MemoryTracker::DisplayInfo();

	return 0;
}



//if (ringo::g_inputSystem.GetMouseButtonDown(0) && !ringo::g_inputSystem.GetMousePrevButtonDown(0)) {
//	std::cout << "left down.\n";
//	std::cout << "x: " << ringo::g_inputSystem.GetMousePosition().x;
//	std::cout << " y: " << ringo::g_inputSystem.GetMousePosition().y;
//	std::cout << "\n";
//}
//if (ringo::g_inputSystem.GetMouseButtonDown(1) && !ringo::g_inputSystem.GetMousePrevButtonDown(1)) {
//	std::cout << "middle down.\n";
//	std::cout << "x: " << ringo::g_inputSystem.GetMousePosition().x;
//	std::cout << " y: " << ringo::g_inputSystem.GetMousePosition().y;
//	std::cout << "\n";
//}
//if (ringo::g_inputSystem.GetMouseButtonDown(2) && !ringo::g_inputSystem.GetMousePrevButtonDown(2)) {
//	std::cout << "right down.\n";
//	std::cout << "x: " << ringo::g_inputSystem.GetMousePosition().x;
//	std::cout << " y: " << ringo::g_inputSystem.GetMousePosition().y;
//	std::cout << "\n";
//}