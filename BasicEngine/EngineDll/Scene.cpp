#include "Scene.h"
#include "ObjectAllocator.h"
#include "Hash.h"
#include <algorithm>

Scene::Scene()
{
	gameObjects.resize(MAX_OBJECTS);
	std::fill(gameObjects.begin(), gameObjects.end(), std::make_pair(-1, nullptr));
}

Scene::~Scene()
{
}

GameObject* Scene::AddGameObject(char* name)
{
	uint32_t hash = hash_str(name);

	ObjectAllocator* objAlloc = ObjectAllocator::GetInstance();
	//Alloc a game object
	GameObject* go = objAlloc->AllocObject();

	int freeIndex = 0;
	while (gameObjects[freeIndex].second != nullptr)
		freeIndex++;

	gameObjects[freeIndex].first = hash;
	gameObjects[freeIndex].second = go;

	std::sort(gameObjects.begin(), gameObjects.end(), [](const std::pair<uint32_t, GameObject*> &left, const std::pair<uint32_t, GameObject*> &right) {
		return left.first < right.first;
	});

	return gameObjects[freeIndex].second;

}

GameObject* Scene::FindGameObject(char* name)
{
	uint32_t hash = hash_str(name);

	std::vector<std::pair<uint32_t, GameObject*>>::iterator lower;

	lower = std::lower_bound(gameObjects.begin(), gameObjects.end(), hash, [](const std::pair<uint32_t, GameObject*> &left, const uint32_t right) {
		return left.first < right;
	});

	int indexFind = lower - gameObjects.begin();
	std::cout << indexFind << std::endl;

	return gameObjects[indexFind].second;
}

void Scene::RemoveGameObject(GameObject *gameObject)
{
	ObjectAllocator* objAlloc = ObjectAllocator::GetInstance();
	//Alloc a game object
	objAlloc->DestroyObject(gameObject);
	int usedIndex = gameObject - gameObjects[0].second;
	gameObjects[usedIndex].second = nullptr;
}
