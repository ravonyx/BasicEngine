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

GameObject* Scene::AddGameObject(const char* name)
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

GameObject* Scene::FindGameObject(const char* name)
{
	uint32_t hash = hash_str(name);

	std::vector<std::pair<uint32_t, GameObject*>>::iterator lower;

	int indexFind = -1;

	for (unsigned int i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects[i].first == hash)
		{
			indexFind = i;
			break;
		}
	}
/*	lower = std::lower_bound(gameObjects.begin(), gameObjects.end(), hash, [](const std::pair<uint32_t, GameObject*> &left, const uint32_t right) {
		return left.first < right;
	});*/

	if (indexFind == -1)
	{
#ifdef _DEBUG
		std::cout << "Game Object was not found" << std::endl;
#endif
		return nullptr;
	}

#ifdef _DEBUG
		std::cout << "Game Object at index " << indexFind << " was found" << std::endl;
#endif
	return gameObjects[indexFind].second;
}

void Scene::RemoveGameObject(GameObject *gameObject)
{
	ObjectAllocator* objAlloc = ObjectAllocator::GetInstance();
	//Alloc a game object
	objAlloc->DestroyObject(gameObject);
	int usedIndex = gameObject - gameObjects[0].second;

	gameObjects[usedIndex].first = -1;
	gameObjects[usedIndex].second = nullptr;
}

void Scene::Update()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if(gameObjects[i].second != nullptr)
			gameObjects[i].second->Update();
	}
}

void Scene::Render(sf::RenderWindow &render_window)
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects[i].second != nullptr)
			gameObjects[i].second->Render(render_window);
	}
}
