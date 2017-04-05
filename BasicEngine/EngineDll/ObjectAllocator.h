#pragma once
#include <vector>
#include "EngineDll.h"

extern "C"
class ENGINEDLL_API ObjectAllocator
{
	private:
		std::vector<GameObject> m_objects;
		
		std::vector<Transform> m_transforms;
		std::vector<Renderer> m_renderers;
		std::vector<Behaviour> m_behaviours;

		int m_indexObject = 0;

		int m_indexTransform = 0;
		int m_indexRenderer = 0;
		int m_indexBehaviour = 0;
		static ObjectAllocator* uniqueInstance;

	public:
		ObjectAllocator();
		virtual ~ObjectAllocator();
		GameObject* AllocObject();
		
		Transform* AllocTransformComp();
		Renderer* AllocRenderComp();
		Behaviour* AllocBehaviourComp();

		static void CreateInstance();
		static ObjectAllocator* GetInstance()
		{
			return uniqueInstance;
		}
};



