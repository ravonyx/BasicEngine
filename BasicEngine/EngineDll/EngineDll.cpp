// EngineDll.cpp : définit les fonctions exportées pour l'application DLL.
//

#include "stdafx.h"
#include "ObjectAllocator.h"

GameObject::GameObject() : isActive(true), name("") 
{
	for (int i = 0; i < __maxCompType; i++)
	{
		m_Components[i] = nullptr;
	}
}
GameObject::GameObject(std::string name) : isActive(true), name(std::move(name)) 
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
/*
void GameObject::AddComponent(EComponentType type)
{
	Component* component;
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
void GameObject::RemoveComponent(EComponentType type)
{
	m_Components[type] = nullptr;
}

/*

GameObjectFactory::GameObjectFactory()
{
	gameObjects.reserve(1024);
}

void GameObjectFactory::AddGameObject(GameObject *gameObj)
{
	gameObjects.emplace_back(gameObj);
}

void GameObjectFactory::RemoveGameObject(GameObject *gameObj)
{
	auto it = std::find(gameObjects.begin(), gameObjects.end(), gameObj);

	if (it != gameObjects.end())
	{
		using std::swap;

		swap(*it, gameObjects.back());
		gameObjects.pop_back();
	}
}*/

ENGINEDLL_API GameObject* CreateGameObjectClass()
{
	GameObject* gameObj = new GameObject();
	return gameObj;
}