
#if defined(YAM2D_DLL_EXPORTS)
#define YAM2D_API __declspec(dllexport)
#elif defined(YAM2D_DLL_IMPORTS)
#define YAM2D_API __declspec(dllimport)
#else
#define YAM2D_API
#endif

