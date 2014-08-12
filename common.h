#ifdef WIN32
#define DLL_EXPORT extern "C" __declspec ( dllimport )
#else
#define DLL_EXPORT extern "C"
#endif