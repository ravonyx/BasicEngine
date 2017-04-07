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

float lerp(float a, float b, float f)
{
	return (a * (1.0 - f)) + (b * f);
}

void TestFunctions();
void MainLoop(sf::RenderWindow &render_window, GUI *gui);

void main()
{
	TestFunctions();

	//Init window and gui
	sfg::Renderer::Set(sfg::VertexArrayRenderer::Create());

	GUI *gui = new GUI();
	gui->Init();

	sf::VideoMode video_mode(800, 600);
	sf::RenderWindow render_window(video_mode, "Hello World example");
	
	MainLoop(render_window, gui);
}

void TestFunctions()
{
	//Get instance of singleton ObjectAllocator
	ObjectAllocator::CreateInstance();
	ObjectAllocator::GetInstance();

	Scene *scene = new Scene();


	GameObject* go0 = scene->AddGameObject("GameObject0");
	GameObject* go1 = scene->AddGameObject("GameObject1");
	GameObject* go2 = scene->AddGameObject("GameObject2");
	GameObject* go3 = scene->AddGameObject("GameObject3");

	//AddComponents;
	go0->AddComponent(GameObject::EComponentType::CTTransform);
	go1->AddComponent(GameObject::EComponentType::CTRenderer);
	go3->AddComponent(GameObject::EComponentType::CTBehaviour);

	//GetComponents
	/*Component* comp = go->GetComponent(GameObject::EComponentType::CTTransform);
	Component* comp2 = go->GetComponent(GameObject::EComponentType::CTBehaviour);*/

	GameObject* go3ex = scene->FindGameObject("GameObject3");

	//Destroy game object
	scene->RemoveGameObject(go0);

	go3ex = scene->FindGameObject("GameObject3");
}

void MainLoop(sf::RenderWindow &render_window, GUI *gui)
{
	using clock = std::chrono::high_resolution_clock;
	std::chrono::nanoseconds lag(0);
	auto time_start = clock::now();

	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Red);
	shape.setPosition(sf::Vector2f(2, 5));

	sf::Event event;
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
		while (lag >= timestep)
		{
			//update(); // update at a fixed rate each time
			lag -= timestep;
		}
		// calculate how close or far we are from the next timestep
		//auto alpha = (float)lag.count() / timestep.count();
		//auto interpolated_state = lerp(current_state, previous_state, alpha);

		gui->Update();

		render_window.clear();
		render_window.draw(shape);
		gui->Display(render_window);
		render_window.display();
	}
}