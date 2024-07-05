#pragma once

#include <GarrysMod/Lua/LuaInterface.h>
#include <GarrysMod/Symbol.hpp>
#include <detouring/hook.hpp>
#include <scanning/symbolfinder.hpp>
#include <vector>

class CBaseEntity;
class CBasePlayer;
class IClient;

namespace Symbols
{
	typedef bool (*DrawSprite)(const Vector &vecOrigin, float flWidth, float flHeight, color32 color);
	const Symbol DrawSpriteSym = Symbol::FromSignature("\x53\x8B\xDC\x83\xEC\x08\x83\xE4\xF0\x83\xC4\x04\x55\x8B\x6B\x04\x89\x6C\x24\x04\x8B\xEC\x81\xEC\x68\x02\x00\x00\xF3"); // 53 8B DC 83 EC 08 83 E4 F0 83 C4 04 55 8B 6B 04 89 6C 24 04 8B EC 81 EC 68 02 00 00 F3
}

namespace Detour
{
	inline bool CheckValue(const char* msg, const char* name, bool ret)
	{
		if (!ret) {
			Msg("[GWater] Failed to %s %s!\n", msg, name);
			return false;
		}

		return true;
	}

	inline bool CheckValue(const char* name, bool ret)
	{
		return CheckValue("get function", name, ret);
	}

	template<class T>
	bool CheckFunction(T func, const char* name)
	{
		return CheckValue("get function", name, func != nullptr);
	}

	extern void* GetFunction(void* module, Symbol symbol);
	extern void Create(Detouring::Hook* hook, const char* name, void* module, Symbol symbol, void* func);
	extern void Remove();
	extern unsigned int g_pCurrentCategory;
}