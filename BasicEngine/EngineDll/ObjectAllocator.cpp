#include "ObjectAllocator.h"
#include <algorithm>

ObjectAllocator* ObjectAllocator::uniqueInstance;

ObjectAllocator::ObjectAllocator()
{
	m_objects.resize(MAX_OBJECTS);
	m_objectsPtr.resize(MAX_OBJECTS);
	std::fill(m_objectsPtr.begin(), m_objectsPtr.end(), false);

	m_transforms.resize(MAX_OBJECTS);
	m_transformsPtr.resize(MAX_OBJECTS);
	std::fill(m_transformsPtr.begin(), m_transformsPtr.end(), false);

	m_renderers.resize(MAX_OBJECTS);
	m_renderersPtr.resize(MAX_OBJECTS);
	std::fill(m_renderersPtr.begin(), m_renderersPtr.end(), false);

	m_behaviours.resize(MAX_OBJECTS);
	m_behavioursPtr.resize(MAX_OBJECTS);
	std::fill(m_behavioursPtr.begin(), m_behavioursPtr.end(), false);
}

ObjectAllocator::~ObjectAllocator()
{
}

void ObjectAllocator::CreateInstance()
{
	if (uniqueInstance == nullptr)
		uniqueInstance = new ObjectAllocator;
}
ObjectAllocator* ObjectAllocator::GetInstance()
{
	return uniqueInstance;
}

GameObject* ObjectAllocator::AllocObject()
{
	int freeIndex = 0;
	while (m_objectsPtr[freeIndex] != false)
		freeIndex++;

	m_objectsPtr[freeIndex] = true;
	return &m_objects[freeIndex];
}
void ObjectAllocator::DestroyObject(GameObject* gameObject)
{
	int usedIndex = gameObject - &m_objects[0];
	//m_objects[freeIndex].clear();
	m_objectsPtr[usedIndex] = false;
}

Transform* ObjectAllocator::AllocTransformComp()
{
	int freeIndex = 0;
	while (m_transformsPtr[freeIndex] != false)
		freeIndex++;

	m_transformsPtr[freeIndex] = true;
	return &m_transforms[freeIndex];
}
void ObjectAllocator::DestroyTransformComp(Transform* transform)
{
	int usedIndex = transform - &m_transforms[0];
	//m_objects[freeIndex].clear();
	m_transformsPtr[usedIndex] = false;
}

Renderer* ObjectAllocator::AllocRenderComp()
{
	int freeIndex = 0;
	while (m_renderersPtr[freeIndex] != false)
		freeIndex++;

	m_renderersPtr[freeIndex] = true;
	return &m_renderers[freeIndex];
}
void ObjectAllocator::DestroyRendererComp(Renderer* renderer)
{
	int usedIndex = renderer - &m_renderers[0];
	//m_objects[freeIndex].clear();
	m_renderersPtr[usedIndex] = false;
}

Behaviour* ObjectAllocator::AllocBehaviourComp()
{
	int freeIndex = 0;
	while (m_behavioursPtr[freeIndex] != false)
		freeIndex++;

	m_behavioursPtr[freeIndex] = true;
	return &m_behaviours[freeIndex];
}
void ObjectAllocator::DestroyBehaviourComp(Behaviour* behaviour)
{
	int usedIndex = behaviour - &m_behaviours[0];
	//m_objects[freeIndex].clear();
	m_behavioursPtr[usedIndex] = false;
}