#include <main.hpp>
#include <GarrysMod/Lua/Interface.h>

#ifdef __APPLE__
	#include <set>
	
	typedef std::set<uint32_t> set_uint32;
#else
	#ifdef _WIN32
		#define WIN32_LEAN_AND_MEAN
	#endif
	
	#include <unordered_set>
	
	typedef std::unordered_set<uint32_t> set_uint32;
#endif

using namespace GarrysMod::Lua;

static SpewOutputFunc_t oldSpewFunc;
static uint32_t gThread, iFloodGateLimit = 100000;

SpewRetval_t spewHandler(SpewType_t spewType, const char *msg) {
	#ifdef _WIN32
		if (GetCurrentThreadId() != gThread)
			return SPEW_CONTINUE;
	#else
		if (getpid() != gThread)
			return SPEW_CONTINUE;
	#endif
	
	if (!msg) //checking if the message is valid
		return SPEW_CONTINUE;

	iFloodGateLimit--;

	if (iFloodGateLimit < 0)
		return SPEW_CONTINUE;

	if (iFloodGateLimit == 0)
		return oldSpewFunc(spewType, "Stopping console flood (floodgate module)");

	return oldSpewFunc(spewType, msg); //pass it back to the default handler
	
}

LUA_FUNCTION_STATIC(ConsoleFloodgate) {
	LUA->CheckType(1, Type::NUMBER);
	iFloodGateLimit = static_cast<uint32_t>(LUA->GetNumber(1));

	return 1;
}

GMOD_MODULE_OPEN() {
	#ifdef _WIN32
		gThread = GetCurrentThreadId();
	#else
		gThread = getpid();
	#endif
	
	oldSpewFunc = GetSpewOutputFunc(); //saving the old func
	SpewOutputFunc((SpewOutputFunc_t)spewHandler); //making our function the spew handler
	
	LUA->PushCFunction(ConsoleFloodgate);
	LUA->SetField(INDEX_GLOBAL, "ConsoleFloodgate");
	return 0;
}

GMOD_MODULE_CLOSE() {
	SpewOutputFunc(oldSpewFunc); //making sure we get out before out lua thingy gets closed and everything breaks
	
	LUA->PushNil();
	LUA->SetField(INDEX_GLOBAL, "ConsoleFloodgate");
	return 0;
}