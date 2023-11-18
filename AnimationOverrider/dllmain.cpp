// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "cAnimationOverrideManager.h"

void Initialize()
{
	// This method is executed when the game starts, before the user interface is shown
	// Here you can do things such as:
	//  - Add new cheats
	//  - Add new simulator classes
	//  - Add new game modes
	//  - Add new space tools
	//  - Change materials
	AnimationOverrideManager.ReadProperties();
}



	virtual_detour(anim_override_detour, Anim::AnimatedCreature, Anim::AnimatedCreature, void(uint32_t, int*)) {    
		void detoured(uint32_t animID, int* pChoice) {

			if (AnimationOverrideManager.overrides.find(animID) == AnimationOverrideManager.overrides.end()) {
				original_function(this, animID, pChoice);
			}
			else {
				AnimationOverride overrider = AnimationOverrideManager.overrides[animID];
				if (overrider.requireAvatar && GameNounManager.GetAvatar() != nullptr && this != GameNounManager.GetAvatar()->mpAnimatedCreature.get()) {
					original_function(this, animID, pChoice);
				}
				else if (overrider.modes_size != 0) {
					bool foundModeID = false;
					for (int i = 0; i < overrider.modes_size; i++) {
						if (overrider.modes[i] == GameModeManager.GetActiveModeID()) {
							foundModeID = true;
							break;
						}
					}
					if (foundModeID) {
						original_function(this, overrider.newID, &overrider.choice);
					}
					else {
						original_function(this, animID, pChoice);
					}
				}
				else {
					original_function(this, overrider.newID, &overrider.choice);
				}
				
			}
		}

	};

void Dispose()
{
	// This method is called when the game is closing
	AnimationOverrideManager.Dispose();
}

void AttachDetours()
{
	// Call the attach() method on any detours you want to add
	// For example: cViewer_SetRenderType_detour::attach(GetAddress(cViewer, SetRenderType));

	anim_override_detour::attach(Address(ModAPI::ChooseAddress(0xA0C5D0, 0xA0C5D0)));
}


// Generally, you don't need to touch any code here
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		ModAPI::AddPostInitFunction(Initialize);
		ModAPI::AddDisposeFunction(Dispose);

		PrepareDetours(hModule);
		AttachDetours();
		CommitDetours();
		break;

	case DLL_PROCESS_DETACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	}
	return TRUE;
}

