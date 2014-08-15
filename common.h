#ifndef COMMON_H
#define COMMON_H

#ifdef WIN32
#define DLL_EXPORT extern "C" __declspec ( dllexport )
#else
#define DLL_EXPORT extern "C"
#endif

#endif // COMMON_H