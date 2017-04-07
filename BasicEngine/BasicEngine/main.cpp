#include <Windows.h>
#include <iostream>

#include "SFML\Graphics.hpp"
#include "GUI.h"
#include "SFGUI\Renderers.hpp"
#include "..\EngineDll\ObjectAllocator.h"
#include "..\EngineDll\GameObject.h"
#include "..\EngineDll\Scene.h"

#include <chrono>

constexpr std::chrono::nanoseconds timestep(16000000);
Scene *scene;

void MainLoop(sf::RenderWindow &render_window, GUI *gui);

void main()
{
	ObjectAllocator::CreateInstance();
	scene = new Scene();

	//Init window and gui
	sfg::Renderer::Set(sfg::VertexArrayRenderer::Create());

	GUI *gui = new GUI(scene);
	gui->Init();

	sf::VideoMode video_mode(800, 600);
	sf::RenderWindow render_window(video_mode, "Basic Engine");
	
	MainLoop(render_window, gui);
}

void MainLoop(sf::RenderWindow &render_window, GUI *gui)
{
	using clock = std::chrono::high_resolution_clock;
	std::chrono::nanoseconds lag(0);
	auto time_start = clock::now();

	sf::CircleShape shape(0.01f);
	shape.setFillColor(sf::Color::Red);
	shape.setPosition(sf::Vector2f(2, 5));
	sf::Event event;
	sf::Clock clockGui;

	gui->Update(0.0f);
	while (render_window.isOpen())
	{
		auto delta_time = clock::now() - time_start;
		time_start = clock::now();
		lag += std::chrono::duration_cast<std::chrono::nanoseconds>(delta_time);

		//Handle events 
		while (render_window.pollEvent(event))
		{
			gui->HandleEvent(event);
			if (event.type == sf::Event::Closed)
			{
				render_window.close();
			}
		}
		// Update the GUI every 5ms
		if (clockGui.getElapsedTime().asMicroseconds() >= 5000)
		{
			// Update() takes the elapsed time in seconds.
			gui->Update(static_cast<float>(clockGui.getElapsedTime().asMicroseconds()) / 1000000.f);
			clockGui.restart();
		}

		while (lag >= timestep)
		{
			//scene->Update();
			//update(); // update at a fixed rate each time
			lag -= timestep;
		}
		// calculate how close or far we are from the next timestep
		//auto alpha = (float)lag.count() / timestep.count();
		//auto interpolated_state = lerp(current_state, previous_state, alpha);

		render_window.clear();

		//render all gameObjects
		scene->Render(render_window);

		//draw at minimum one shape / else UI is not displayed
		render_window.draw(shape);

		gui->Display(render_window);
		render_window.display();
	}
}