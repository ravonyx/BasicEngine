// EngineDll.cpp : définit les fonctions exportées pour l'application DLL.
//

#include "stdafx.h"
#include "EngineDll.h"

//example for variable
ENGINEDLL_API int nEngineDll=0;
//example for class
CEngineDll::CEngineDll()
{
	return;
}

// name mangling : le C++ va modifier le nom des symboles afin de les distinguer 
//Dans ce cas il faut forcer la convention C avec extern "C"

ENGINEDLL_API int InitFacialAnimation(void)
{
    return 42;
}

