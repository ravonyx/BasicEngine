#pragma once

enum EComponentType
{
	CTRenderer = 0,
	CTBehaviour,
	CTTransform,
	__maxCompType
};

class GameObjectInterface
{
	private:
		bool isActive;
		std::string name;
		Component*	m_Components[__maxCompType];
	public:
	
		virtual void AddComponent(EComponentType type) = 0;
		virtual void RemoveComponent(EComponentType type) = 0;
};

