/** 
 * < Rewind Engine > Common.h
 * Author: DeckardZ46
 * Date: 2024/07/10
 * Note: This is common settings for Rewind Engine
 * Codebase: https://github.com/DeckardZ46/RewindEngine
*/

// assertions
#ifdef Rwd_ENABLE_ASSERT
	#define Rwd_ASSERT(x, ...) { if(!(x)) { NLOGE("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define EDITOR_ASSERT(x, ...) { if(!(x)) { ELOGE("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define Rwd_ASSERT(x,...)
	#define EDITOR_ASSERT(x,...)
#endif

// settings
#ifdef Rwd_PLAT_WINDOWS
    // OpenGL version settings, version = MAJ.MIN, e.g. 3.3
    #define Rwd_OGL_VER_MAJ 3  
    #define Rwd_OGL_VER_MIN 3  
#endif