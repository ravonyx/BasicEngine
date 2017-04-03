#include <Windows.h>
#include <iostream>
#include <cstdint>
#include <map>
#include <unordered_map>
#include <new>

#define FNV1_32_INIT ((uint32_t)0x811c9dc5)

class SimpleObject
{
	float x, y;
public:
	SimpleObject() :x(3.14f), y(42.0f) {}
};

class Object
{
	std::string s;
	int i;
	float f;
public:
	Object() : i(0), f(0.0f), s("")
	{}
	~Object()
	{}
	//new c++11 : move constructor
	Object(Object&& o) : i(o.i), f(o.f), s(std::move(o.s))
	{

	}
	//new c++11 : move assignement
	Object& operator =(const Object&& o)
	{
		i = o.i;
		f = o.f;
		s = std::move(o.s);
		return *this;
	}

	/*void ModifyObject(Object& a, Object& b)
	{
	b = a;
	b.f += b.i;
	}*/
};

class Singleton
{
	static Singleton* uniqueInstance;

public:
	static void CreateInstance()
	{
		if (uniqueInstance == nullptr)
			uniqueInstance = new Singleton;
	}
	Singleton& getInstance()
	{
		return *uniqueInstance;
	}
};

typedef int(*dllFunction)();

char* freespace;
using hash_value = uint32_t;
using texture = uint32_t;

uint32_t fnv_32a_str(char *str, uint32_t hval = FNV1_32_INIT);
void MainLoop();

// 1. trop de comparaison de string
std::map<std::string, texture> annuaire_map;
// 2. simplification des comparaisons, alloc. de nodes
std::map<hash_value, texture> annuaire_hash_map;
// 3. simplification des comparaisons, mais alloc. de string
std::unordered_map<std::string, texture> unordered_map;
// 4. afin d eviter les alloc., on utiilise un vector (les elements sont contigues en mémoire)
// on doit obtenir l ordre du vector
using annuaire_paire = std::pair<hash_value, texture>;
std::vector<annuaire_paire> annuaire_vec;
// utiliqez std::lower_bound() : suppose element triès

//Methode 1 : on attend que ts les elemens aient été insérés puis std::sort
//Methode 2 : on trie a chaque insertion

//Utiliser emplace_back a la place de push_back
//				en moyenne | deja trié
//quicksort: O()  nLog(n)  |    n2
//bubllesort: O()   n2	   |    n

//Exemple : le Fname de UE4
struct Fname
{
	uint32_t hash;
#ifndef RELEASE
	std::string debug_str;
#endif // !RELEASE
};

void main()
{
	//Linear allocator
	char* arena = new char[1024 * 1024];
	freespace = arena;

	std::vector<Object> Pool;
	Pool.resize(1024);
	std::vector<Object*> FreeListPointers;
	FreeListPointers.resize(1024);
	Object* FreeList = FreeListPointers[0];
	// a l init tout les pointeurs pointent sur le successeur
	for (int index = 0; index < 1024 - 1; ++index)
	{
		FreeListPointers[index] = FreeListPointers[index + 1];
	}
	FreeListPointers[1023] = nullptr;

	//Exemple d'allocation d'un objet
	// 1. calcul de l'index;
	int index = FreeList - FreeListPointers[0];
	// 2. retourner le pointeur disponible




	//Hash String

	//cle = std:::string -> alloc. string
	annuaire_map["ma_texture"] = 0x12345;
	annuaire_map["second_texture"] = 0xabcd;

	uint32_t hashLookup = fnv_32a_str("ma_texture");
	//plrs comparaisons de string -> trouver element recherché
	auto iter = annuaire_hash_map.find(hashLookup);
	if (iter != annuaire_hash_map.end())
	{
	}
	uint32_t hash = fnv_32a_str("Hello");




	// Use Dll

	HMODULE dll = LoadLibrary(L"EngineDll");
	dllFunction InitFacialAnimation = (dllFunction) GetProcAddress(dll, "InitFacialAnimation");
	int val = InitFacialAnimation();
	FreeLibrary(dll);

	std::cout << std::endl;

	MainLoop();
}

uint32_t fnv_32a_str(char *str, uint32_t hval)
{
	/* unsigned string */
	unsigned char *s = (unsigned char *)str;	
	//hash each octet
	while (*s) 
	{
		/* xor the bottom with the current octet */
		hval ^= (uint32_t)*s++;

		/* multiply by the 32 bit FNV magic prime mod 2^32 */
#if defined(NO_FNV_GCC_OPTIMIZATION)
		hval *= FNV_32_PRIME;
#else
		hval += (hval << 1) + (hval << 4) + (hval << 7) + (hval << 8) + (hval << 24);
#endif
	}
	return hval;
}


void MainLoop()
{
	//placement new: construit l'object a l'adresse spécifiée
	auto obj = new (freespace)SimpleObject;
	//allocation d'un nouvel objet
	freespace += sizeof(SimpleObject);

	//appel explicite au desructeur
	obj->~SimpleObject();
}