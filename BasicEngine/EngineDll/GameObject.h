#pragma once

#include "EngineDll.h"

#include <iostream>
#include <vector>
#include "SFML\Graphics.hpp"

#define MAX_OBJECTS 1024

extern "C"
class ENGINEDLL_API Component
{
public:
	virtual void Update() {}
	virtual void Render(sf::RenderWindow &render_window) {}
};

extern "C"
class ENGINEDLL_API Transform : public Component
{
private:
	float x;
	float y;

public:
	Transform() : x(0.0f), y(0.0f) {}
	~Transform() {}
};

extern "C"
class ENGINEDLL_API Behaviour : public Component
{
public:
	Behaviour() {}
	~Behaviour() {}
};

extern "C"
class ENGINEDLL_API Renderer : public Component
{
	private:
		sf::CircleShape shape;
	public:
		Renderer();
		~Renderer() {}
		void Render(sf::RenderWindow &render_window);

};

extern "C"
class ENGINEDLL_API GameObject
{
public:
	enum EComponentType
	{
		CTRenderer = 0,
		CTBehaviour,
		CTTransform,
		__maxCompType
	};

	GameObject();
	GameObject(std::string name);
	//new c++11 : move constructor
	GameObject(const GameObject&& gameObj);
	GameObject(const GameObject& gameObj);
	~GameObject();

	void AddComponent(EComponentType type);
	void RemoveComponent(EComponentType type);
	Component* GetComponent(EComponentType type);

	//new c++11 : move assignement
	GameObject& operator =(const GameObject&& gameObj);
	GameObject& operator =(const GameObject& gameObj);


	void Update();
	void Render(sf::RenderWindow &render_window);

private:
	bool isActive = true;
	bool isDead = false;
	std::string name = "";
	Component*	m_Components[__maxCompType];
};
