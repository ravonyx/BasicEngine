#pragma once
#include <vector>
#include "EngineDll.h"
#include "GameObject.h"

extern "C"
class ENGINEDLL_API ObjectAllocator
{
	private:
		std::vector<GameObject> m_objects;
		std::vector<bool> m_objectsPtr;
		
		std::vector<Transform> m_transforms;
		std::vector<bool> m_transformsPtr;
		std::vector<Renderer> m_renderers;
		std::vector<bool> m_renderersPtr;
		std::vector<Behaviour> m_behaviours;
		std::vector<bool> m_behavioursPtr;

		int m_indexObject = 0;

		int m_indexTransform = 0;
		int m_indexRenderer = 0;
		int m_indexBehaviour = 0;
		static ObjectAllocator* uniqueInstance;

	public:
		ObjectAllocator();
		virtual ~ObjectAllocator();

		GameObject* AllocObject();
		void DestroyObject(GameObject* gameObject);

		Transform* AllocTransformComp();
		void DestroyTransformComp(Transform* transform);

		Renderer* AllocRenderComp();
		void DestroyRendererComp(Renderer* renderer);

		Behaviour* AllocBehaviourComp();
		void DestroyBehaviourComp(Behaviour* behaviour);

		static void CreateInstance();
		static ObjectAllocator* GetInstance();
};



