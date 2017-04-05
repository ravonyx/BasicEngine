// Le bloc ifdef suivant est la façon standard de créer des macros qui facilitent l'exportation 
// à partir d'une DLL. Tous les fichiers contenus dans cette DLL sont compilés avec le symbole ENGINEDLL_EXPORTS
// défini sur la ligne de commande. Ce symbole ne doit pas être défini pour un projet
// qui utilisent cette DLL. De cette manière, les autres projets dont les fichiers sources comprennent ce fichier considèrent les fonctions 
// ENGINEDLL_API comme étant importées à partir d'une DLL, tandis que cette DLL considère les symboles
// définis avec cette macro comme étant exportés.
#ifdef ENGINEDLL_EXPORTS
#define ENGINEDLL_API __declspec(dllexport)
#else
#define ENGINEDLL_API __declspec(dllimport)
#endif

#include <iostream>
#include <vector>

#define MAX_OBJECTS 1024

extern "C"
class ENGINEDLL_API Component
{
public:
	virtual void Update() {}
	virtual void Render() {}
};

extern "C"
class ENGINEDLL_API Transform : public Component
{
private:
	float x;
	float y;

public:
	Transform() : x(0.0f), y(0.0f) {}
	~Transform(){}
};

extern "C"
class ENGINEDLL_API Behaviour : public Component
{
public:
	Behaviour() {}
	~Behaviour() {}
};
extern "C"
class ENGINEDLL_API Renderer : public Component
{
public:
	Renderer() {}
	~Renderer() {}
};

extern "C"
class ENGINEDLL_API GameObject 
{
	private:
		bool isActive;
		std::string name;

		enum EComponentType
		{
			CTRenderer = 0,
			CTBehaviour,
			CTTransform,
			__maxCompType
		};
		Component*	m_Components[__maxCompType];

	public:
		GameObject();
		GameObject(std::string name);
		//new c++11 : move constructor
		GameObject(const GameObject&& gameObj);
		GameObject(const GameObject& gameObj);
		~GameObject()
		{

		}

		void GameObject::AddComponent(EComponentType type);
		void GameObject::RemoveComponent(EComponentType type);

		//new c++11 : move assignement
		GameObject& operator =(const GameObject&& gameObj);
		GameObject& operator =(const GameObject& gameObj);
};
/*

class ENGINEDLL_API GameObjectFactory
{
private:
	std::vector<GameObject*> gameObjects;
public:
	GameObjectFactory();

	void AddGameObject(GameObject *gameObj);
	void RemoveGameObject(GameObject *gameObj);
};
*/

extern "C"
ENGINEDLL_API GameObject* CreateGameObjectClass();
