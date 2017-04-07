#include "GUI.h"
#include "SFGUI\Renderers.hpp"

GUI::GUI(Scene *scene) : scene(scene)
{
	window = sfg::Window::Create();
	desktop.Add(window);
}

void GUI::Init()
{
	// Create a box with 20 pixels spacing.
	auto boxV = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 20.f);

	auto boxH1 = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);

	createGameObject = sfg::Button::Create("Create Game Object");
	createGameObject->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&GUI::OnCreateGameObject, this));
	nameToCreate = sfg::Entry::Create();
	nameToCreate->SetRequisition(sf::Vector2f(80.f, 0.f));

	boxH1->Pack(nameToCreate);
	boxH1->Pack(createGameObject);
	boxH1->SetSpacing(5.f);

	auto boxH2 = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);

	destroyGameObject = sfg::Button::Create("Destroy Game Object");
	destroyGameObject->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&GUI::OnDestroyGameObject, this));
	nameToDestroy = sfg::Entry::Create();
	nameToDestroy->SetRequisition(sf::Vector2f(80.f, 0.f));

	boxH2->Pack(nameToDestroy);
	boxH2->Pack(destroyGameObject);
	boxH2->SetSpacing(5.f);

	auto boxH3 = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);

	findGameObject = sfg::Button::Create("Find Game Object");
	findGameObject->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&GUI::OnFindGameObject, this));
	nameToFind = sfg::Entry::Create();
	nameToFind->SetRequisition(sf::Vector2f(80.f, 0.f));

	boxH3->Pack(nameToFind);
	boxH3->Pack(findGameObject);
	boxH3->SetSpacing(5.f);

	boxV->Pack(boxH1);
	boxV->Pack(boxH2);
	boxV->Pack(boxH3);

	window->SetTitle("Manage Game Objets");
	window->Add(boxV);
}

void GUI::Update(float time)
{
	desktop.Update(time);
}
void GUI::HandleEvent(sf::Event event)
{
	desktop.HandleEvent(event);
}
void GUI::Display(sf::RenderWindow &render_window)
{
	sfgui.Display(render_window);
}

void GUI::OnCreateGameObject()
{
	std::string name = nameToCreate->GetText().toAnsiString();
	if (name != "")
	{
		const char* nameToCreate = name.c_str();
		GameObject* go = scene->AddGameObject(nameToCreate);
#ifdef _DEBUG
		std::cout << "Game Object created with name " << name << std::endl;
#endif
	}
}

void GUI::OnDestroyGameObject()
{
	std::string name = nameToDestroy->GetText().toAnsiString();
	if (name != "")
	{
		const char* nameToDestroy = name.c_str();
		GameObject* go = scene->FindGameObject(nameToDestroy);
		scene->RemoveGameObject(go);
#ifdef _DEBUG
		std::cout << "Game Object with name " << name  << " was destroyed" << std::endl;
#endif
	}
}

void GUI::OnFindGameObject()
{
	std::string name = nameToFind->GetText().toAnsiString();
	if (name != "")
	{
		const char* nameToFind = name.c_str();
		GameObject* go = scene->FindGameObject(nameToFind);
#ifdef _DEBUG
		if(go != nullptr)
			std::cout << "Game Object with name " << name << " was found" << std::endl;
#endif
	}
}