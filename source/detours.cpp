#include "detours.h"
#include <map>

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

unsigned int g_pCurrentCategory = 0;

SymbolFinder symfinder;
void* Detour::GetFunction(void* module, Symbol symbol)
{
	return symfinder.Resolve(module, symbol.name.c_str(), symbol.length);
}

std::vector<Detouring::Hook*> g_pDetours = {};
void Detour::Create(Detouring::Hook* hook, const char* name, void* module, Symbol symbol, void* hook_func)
{
	void* func = Detour::GetFunction(module, symbol);
	if (!CheckFunction(func, name))
		return;

	hook->Create(func, hook_func);
	hook->Enable();

	g_pDetours.push_back(hook);

	if (!hook->IsValid()) {
		Msg("Failed to detour %s!\n", name);
	}
}

void Detour::Remove() // NOTE: Do we need to check if the provided category is valid?
{
	for (Detouring::Hook* hook : g_pDetours) {
		if (hook->IsEnabled())
		{
			hook->Disable();
			hook->Destroy();
		}
	}
	g_pDetours.clear();
}