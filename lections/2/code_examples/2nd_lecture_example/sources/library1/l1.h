#ifdef WIN32
#ifdef library1_EXPORTS
#define WINLIB __declspec(dllexport)
#else
#define WINLIB __declspec(dllimport)
#endif
#else
#define WINLIB
#endif

extern "C"
{
	WINLIB void a1();
}
