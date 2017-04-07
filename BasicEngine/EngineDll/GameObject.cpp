#include "GameObject.h"

#include "stdafx.h"
#include "ObjectAllocator.h"

GameObject::GameObject()
{
	for (int i = 0; i < __maxCompType; i++)
	{
		m_Components[i] = nullptr;
	}
}
GameObject::GameObject(std::string name): name(std::move(name))
{
	for (int i = 0; i < __maxCompType; i++)
	{
		m_Components[i] = nullptr;
	}
}
//new c++11 : move constructor
GameObject::GameObject(const GameObject&& gameObj) : isActive(gameObj.isActive), name(std::move(gameObj.name))
{
	//TODO : set components
}
GameObject::GameObject(const GameObject& gameObj) : isActive(gameObj.isActive), name(std::move(gameObj.name))
{
	//TODO : set components
}


GameObject & GameObject::operator=(const GameObject && gameObj)
{
	isActive = gameObj.isActive;
	name = std::move(gameObj.name);
	return *this;
}
GameObject& GameObject::operator =(const GameObject& gameObj)
{
	isActive = gameObj.isActive;
	name = std::move(gameObj.name);
	return *this;
}

void GameObject::AddComponent(EComponentType type)
{
	Component* component = nullptr;
	ObjectAllocator* objAlloc = ObjectAllocator::GetInstance();
	if (type == CTTransform)
	{
		Transform *transform = objAlloc->AllocTransformComp();
		component = transform;
	}
	else if (type == CTRenderer)
	{
		Renderer *renderer = objAlloc->AllocRenderComp();
		component = renderer;
	}
	else if (type == CTBehaviour)
	{
		Behaviour *behaviour = objAlloc->AllocBehaviourComp();
		component = behaviour;
	}
	m_Components[type] = component;
}

Component* GameObject::GetComponent(EComponentType type)
{
	return m_Components[type];
}

void GameObject::RemoveComponent(EComponentType type)
{
	m_Components[type] = nullptr;
}

GameObject::~GameObject()
{
	for (int i = 0; i < __maxCompType; i++)
	{
		m_Components[i] = nullptr;
	}
}

void GameObject::Update()
{
	for (int i = 0; i < __maxCompType; i++)
	{
		if(m_Components[i] != nullptr)
			m_Components[i]->Update();
	}
}

void GameObject::Render(sf::RenderWindow &render_window)
{
	for (int i = 0; i < __maxCompType; i++)
	{
		if (m_Components[i] != nullptr)
			m_Components[i]->Render(render_window);
	}
}


Renderer::Renderer()
{
	shape = sf::CircleShape(100.f);
	shape.setFillColor(sf::Color::Green);
	shape.setPosition(sf::Vector2f(2, 5));
}

void Renderer::Render(sf::RenderWindow &render_window)
{
	render_window.draw(shape);
}