#include <Windows.h>
#include <iostream>
#include <cstdint>
#include "SFML\Graphics.hpp"
#include "GUI.h"
#include "SFGUI\Renderers.hpp"
#include "GameObjectInterface.h"

typedef GameObjectInterface *(*dllFunction)();

void main()
{
	// Use Dll

	HMODULE dll = LoadLibrary(L"EngineDll");
	dllFunction CreateGameObjectInstance = (dllFunction)GetProcAddress(dll, "CreateGameObjectClass");
	GameObjectInterface *gameObj = CreateGameObjectInstance();
	gameObj->AddComponent(CTTransform);

	//int val = InitFacialAnimation();

	//GameObjectInterface *(*test_fun)() = (GameObjectInterface *(*test_fun)())GetProcAddress(hInstLibrary, "allocate_test");
	//GameObjectInterface *test_ptr = test_fun();
	//test_ptr->Function(12); //use you object

	FreeLibrary(dll);

	sfg::Renderer::Set(sfg::VertexArrayRenderer::Create());

	GUI *gui = new GUI();
	gui->Init();

	sf::VideoMode video_mode(800, 600);
	sf::RenderWindow render_window(video_mode, "Hello World example");
	sf::Event event;

	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Red);
	shape.setPosition(sf::Vector2f(2, 5));

	while (render_window.isOpen())
	{
		while (render_window.pollEvent(event))
		{
			gui->HandleEvent(event);
			if (event.type == sf::Event::Closed)
			{
				render_window.close();
			}
		}
		gui->Update();

		render_window.clear();
		render_window.draw(shape);
		gui->Display(render_window);
		render_window.display();
	}

	//MainLoop();
}
