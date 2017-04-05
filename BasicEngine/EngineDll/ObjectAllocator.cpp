#include "ObjectAllocator.h"

ObjectAllocator* ObjectAllocator::uniqueInstance;

ObjectAllocator::ObjectAllocator()
{
	m_objects.resize(MAX_OBJECTS);

	m_transforms.resize(MAX_OBJECTS);
	m_renderers.resize(MAX_OBJECTS);
	m_behaviours.resize(MAX_OBJECTS);
}

ObjectAllocator::~ObjectAllocator()
{
}

void ObjectAllocator::CreateInstance()
{
	if (uniqueInstance == nullptr)
		uniqueInstance = new ObjectAllocator;
}

GameObject* ObjectAllocator::AllocObject()
{
	return &m_objects[m_indexObject++];
}

Transform* ObjectAllocator::AllocTransformComp()
{
	return &m_transforms[m_indexTransform++];

}
Renderer* ObjectAllocator::AllocRenderComp()
{
	return &m_renderers[m_indexRenderer++];

}
Behaviour* ObjectAllocator::AllocBehaviourComp()
{
	return &m_behaviours[m_indexBehaviour++];
}
