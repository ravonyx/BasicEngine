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

	auto boxH1 = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5.0f);

	createGameObject = sfg::Button::Create("Create Game Object");
	createGameObject->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&GUI::OnCreateGameObject, this));
	nameToCreate = sfg::Entry::Create();
	nameToCreate->SetRequisition(sf::Vector2f(80.f, 0.f));

	boxH1->Pack(nameToCreate);
	boxH1->Pack(createGameObject);

	auto boxH2 = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5.0f);

	destroyGameObject = sfg::Button::Create("Destroy Game Object");
	destroyGameObject->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&GUI::OnDestroyGameObject, this));
	nameToDestroy = sfg::Entry::Create();
	nameToDestroy->SetRequisition(sf::Vector2f(80.f, 0.f));

	boxH2->Pack(nameToDestroy);
	boxH2->Pack(destroyGameObject);

	auto boxH3 = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5.0f);

	findGameObject = sfg::Button::Create("Find Game Object");
	findGameObject->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&GUI::OnFindGameObject, this));
	nameToFind = sfg::Entry::Create();
	nameToFind->SetRequisition(sf::Vector2f(80.f, 0.f));

	boxH3->Pack(nameToFind);
	boxH3->Pack(findGameObject);

	auto boxV1 = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.0f);

	nameForComp = sfg::Entry::Create();
	nameForComp->SetRequisition(sf::Vector2f(80.f, 0.f));

	auto boxH4 = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5.0f);
	addTransformComp = sfg::Button::Create("Add Transform");
	addTransformComp->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&GUI::OnAddTransform, this));
	addBehaviourComp = sfg::Button::Create("Add Behaviour");
	addBehaviourComp->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&GUI::OnAddBehaviour, this));
	addRenderComp = sfg::Button::Create("Add Renderer");
	addRenderComp->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&GUI::OnAddRenderer, this));

	boxH4->Pack(addTransformComp);
	boxH4->Pack(addBehaviourComp);
	boxH4->Pack(addRenderComp);

	auto boxH5 = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5.0f);
	destroyTransformComp = sfg::Button::Create("Destroy Transform");
	destroyTransformComp->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&GUI::OnDestroyTransform, this));
	destroyBehaviourComp = sfg::Button::Create("Destroy Behaviour");
	destroyBehaviourComp->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&GUI::OnDestroyBehaviour, this));
	destroyRenderComp = sfg::Button::Create("Destroy Renderer");
	destroyRenderComp->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&GUI::OnDestroyRenderer, this));

	boxH5->Pack(destroyTransformComp);
	boxH5->Pack(destroyBehaviourComp);
	boxH5->Pack(destroyRenderComp);

	boxV1->Pack(nameForComp);
	boxV1->Pack(boxH4);
	boxV1->Pack(boxH5);

	boxH3->Pack(nameToFind);
	boxH3->Pack(findGameObject);

	boxV->Pack(boxH1);
	boxV->Pack(boxH2);
	boxV->Pack(boxH3);
	boxV->Pack(boxV1);

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

void GUI::OnAddTransform()
{
	std::string name = nameForComp->GetText().toAnsiString();
	if (name != "")
	{
		const char* nameForComp = name.c_str();
		GameObject* go = scene->FindGameObject(nameForComp);
		if (go != nullptr)
		{
			go->AddComponent(GameObject::EComponentType::CTTransform);
#ifdef _DEBUG
			std::cout << "Add Transform Component to Game Object " << name << std::endl;
#endif
		}
	}
}
void GUI::OnAddBehaviour()
{
	std::string name = nameForComp->GetText().toAnsiString();
	if (name != "")
	{
		const char* nameForComp = name.c_str();
		GameObject* go = scene->FindGameObject(nameForComp);
		if (go != nullptr)
		{
			go->AddComponent(GameObject::EComponentType::CTBehaviour);
#ifdef _DEBUG
			std::cout << "Add Behaviour Component to Game Object " << name << std::endl;
#endif
		}
	}
}
void GUI::OnAddRenderer()
{
	std::string name = nameForComp->GetText().toAnsiString();
	if (name != "")
	{
		const char* nameForComp = name.c_str();
		GameObject* go = scene->FindGameObject(nameForComp);
		if (go != nullptr)
		{
			go->AddComponent(GameObject::EComponentType::CTRenderer);
#ifdef _DEBUG
			std::cout << "Add Renderer Component to Game Object " << name << std::endl;
#endif
		}
	}
}

void GUI::OnDestroyTransform()
{
	std::string name = nameForComp->GetText().toAnsiString();
	if (name != "")
	{
		const char* nameForComp = name.c_str();
		GameObject* go = scene->FindGameObject(nameForComp);
		if (go != nullptr)
		{
			go->RemoveComponent(GameObject::EComponentType::CTTransform);
#ifdef _DEBUG
			std::cout << "Destroy Transform Component to Game Object " << name << std::endl;
#endif
		}
	}
}
void GUI::OnDestroyBehaviour()
{
	std::string name = nameForComp->GetText().toAnsiString();
	if (name != "")
	{
		const char* nameForComp = name.c_str();
		GameObject* go = scene->FindGameObject(nameForComp);
		if (go != nullptr)
		{
			go->RemoveComponent(GameObject::EComponentType::CTBehaviour);
#ifdef _DEBUG
			std::cout << "Destroy Behaviour Component to Game Object " << name << std::endl;
#endif
		}
	}
}
void GUI::OnDestroyRenderer()
{
	std::string name = nameForComp->GetText().toAnsiString();
	if (name != "")
	{
		const char* nameForComp = name.c_str();
		GameObject* go = scene->FindGameObject(nameForComp);
		if (go != nullptr)
		{
			go->RemoveComponent(GameObject::EComponentType::CTRenderer);
#ifdef _DEBUG
			std::cout << "Destroy Renderer Component to Game Object " << name << std::endl;
#endif
		}
	}
}