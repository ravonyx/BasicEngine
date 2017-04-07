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

		void Update();
		void Render(sf::RenderWindow &render_window);

		GameObject* AddGameObject(const char* name);
		GameObject* FindGameObject(const char* name);
		void RemoveGameObject(GameObject *gameObj);
};

