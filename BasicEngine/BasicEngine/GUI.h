#pragma once

#include "SFML\Graphics.hpp"
#include "SFGUI\SFGUI.hpp"
#include "SFGUI\Desktop.hpp"
#include "SFGUI\Window.hpp"
#include "SFGUI\Button.hpp"
#include "SFGUI\Label.hpp"
#include "SFGUI\Box.hpp"
#include "SFGUI\Entry.hpp"

#include "..\EngineDll\Scene.h"

class GUI
{
	private:
		Scene *scene;
		sfg::SFGUI sfgui;
		sfg::Desktop desktop;
		sfg::Window::Ptr window;

		sfg::Button::Ptr createGameObject;
		sfg::Button::Ptr destroyGameObject;
		sfg::Button::Ptr findGameObject;

		sfg::Entry::Ptr nameToCreate;
		sfg::Entry::Ptr nameToDestroy;
		sfg::Entry::Ptr nameToFind;

		sfg::Entry::Ptr nameForComp;
		sfg::Button::Ptr addTransformComp;
		sfg::Button::Ptr addBehaviourComp;
		sfg::Button::Ptr addRenderComp;

		sfg::Button::Ptr destroyTransformComp;
		sfg::Button::Ptr destroyBehaviourComp;
		sfg::Button::Ptr destroyRenderComp;

		void OnCreateGameObject();
		void OnDestroyGameObject();
		void OnFindGameObject();

		void OnAddTransform();
		void OnAddBehaviour();
		void OnAddRenderer();

		void OnDestroyTransform();
		void OnDestroyBehaviour();
		void OnDestroyRenderer();

	public:
		GUI(Scene *scene);
		void Init();
		void Update(float time);
		void HandleEvent(sf::Event event);
		void Display(sf::RenderWindow &render_window);
};