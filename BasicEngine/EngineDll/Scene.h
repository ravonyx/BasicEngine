#pragma once

#include "GameObject.h"

using hash_value = uint32_t;

class ENGINEDLL_API Scene
{
	private:
		std::vector<std::pair<hash_value, GameObject*>> gameObjects;

	public:
		Scene();
		~Scene();

		GameObject* AddGameObject(char* name);
		GameObject* FindGameObject(char* name);
		void RemoveGameObject(GameObject *gameObj);
};

