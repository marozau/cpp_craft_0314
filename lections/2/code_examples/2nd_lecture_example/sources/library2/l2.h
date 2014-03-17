#ifdef WIN32
#ifdef library2_EXPORTS
#define WINLIB __declspec(dllexport)
#else
#define WINLIB __declspec(dllimport)
#endif
#else
#define WINLIB
#endif

#include "pl.h"

extern "C"
{
	WINLIB void a1();
	WINLIB void a2();
}
