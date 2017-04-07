#include "GUI.h"
#include "SFGUI\Renderers.hpp"

GUI::GUI()
{
	window = sfg::Window::Create();
	desktop.Add(window);
}

void GUI::Init()
{
	// Create a box with 20 pixels spacing.
	auto box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 20.f);

	create_cube_btn = sfg::Button::Create("Create Game Object");
	label_cube = sfg::Label::Create("Cube");
	//GUI gui;
	create_cube_btn->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&GUI::OnButtonClick, this));
	window->SetTitle("Create Game Objets");
	window->Add(box);

	box->Pack(create_cube_btn);
	box->Pack(label_cube);

}

void GUI::Update()
{
	desktop.Update(1.0f);
}
void GUI::HandleEvent(sf::Event event)
{
	desktop.HandleEvent(event);
}
void GUI::Display(sf::RenderWindow &render_window)
{
	sfgui.Display(render_window);
}

void GUI::OnButtonClick()
{
	create_cube_btn->SetLabel("Cube created !");
}
