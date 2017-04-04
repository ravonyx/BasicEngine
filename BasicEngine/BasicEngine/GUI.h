#pragma once

#include "SFML\Graphics.hpp"
#include "SFGUI\SFGUI.hpp"
#include "SFGUI\Desktop.hpp"
#include "SFGUI\Window.hpp"
#include "SFGUI\Button.hpp"
#include "SFGUI\Label.hpp"
#include "SFGUI\Box.hpp"

class GUI
{
	private:
		sfg::SFGUI sfgui;
		sfg::Desktop desktop;
		sfg::Window::Ptr window;

		sfg::Button::Ptr create_cube_btn;
		sfg::Label::Ptr label_cube;
		sfg::Box::Ptr box;

		void OnButtonClick();

	public:
		GUI();
		void Init();
		void Update();
		void HandleEvent(sf::Event event);
		void Display(sf::RenderWindow &render_window);
};