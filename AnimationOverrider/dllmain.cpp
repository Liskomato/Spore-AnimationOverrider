// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

void Initialize()
{
	// This method is executed when the game starts, before the user interface is shown
	// Here you can do things such as:
	//  - Add new cheats
	//  - Add new simulator classes
	//  - Add new game modes
	//  - Add new space tools
	//  - Change materials
}



	virtual_detour(anim_override_detour, Anim::AnimatedCreature, Anim::AnimatedCreature, void(uint32_t, int*)) {    
		void detoured(uint32_t animID, int* pChoice) {
			PropertyListPtr propList; // .prop file for the animation ID
			uint32_t newID;			  // ID that we will override the old value with.
			uint32_t* modes;	      // Array of game mode IDs override will activate in.
			size_t modes_size;        // Size of game mode ID array
			bool requireAvatar;       // Require avatar for the override
			int* choice = pChoice;    // animation ID choice.

			/// 
			/// First check that the prop file with the same ID as our original animation exists in AnimationOverrides.
			/// overrideWith is the new ID we use instead in this detour, and it is required to exist for the override to work.
			/// forceChoice is optional but it can help to force a specific animation choice in the new animation.
			/// requireAvatar makes sure only the avatar is the one whose animations are overwritten with this override in particular.
			/// modes is the list of valid game mode IDs that trigger the override (optional)
			/// 
			if (PropManager.GetPropertyList(animID, id("AnimationOverrides"), propList) &&
				propList->HasProperty(id("overrideWith")) &&
				App::Property().GetUInt32(propList.get(), id("overrideWith"), newID)) {
				App::Property().GetInt32(propList.get(), id("forceChoice"), *choice);
				if (App::Property().GetBool(propList.get(),id("requireAvatar"),requireAvatar) && requireAvatar && 
					GameNounManager.GetAvatar() != nullptr && this != GameNounManager.GetAvatar()->mpAnimatedCreature.get()) {
					original_function(this, animID, pChoice);
				}
				else if (App::Property().GetArrayUInt32(propList.get(),id("modes"),modes_size,modes)) {
					bool matchID = false;
					for (int i = 0; i < modes_size; i++) {
						if (modes[i] == GameModeManager.GetActiveModeID()) {
							matchID = true;
							break;
						}
					}
					if (matchID) {
						original_function(this, newID,choice);
					}
					else {
						original_function(this, animID,pChoice);
					}
				}
				else {
					original_function(this, newID, choice);
				}
			}
			else {
				original_function(this, animID, pChoice);
			}
		}

	};

void Dispose()
{
	// This method is called when the game is closing
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

