#include "stdafx.h"
#include "cAnimationOverrideManager.h"

cAnimationOverrideManager::cAnimationOverrideManager()
{
}


cAnimationOverrideManager::~cAnimationOverrideManager()
{
}

void cAnimationOverrideManager::ReadProperties() {
	
	vector<uint32_t> IDs;
	if (PropManager.GetPropertyListIDs(id("AnimationOverrides"), IDs)) {
		for each (uint32_t ID in IDs) {
			PropertyListPtr list;
			if (PropManager.GetPropertyList(ID, id("AnimationOverrides"), list)) {
				AnimationOverride entry;
				if (App::Property::GetUInt32(list.get(), id("overrideWith"), entry.newID)) {
					App::Property::GetInt32(list.get(),id("forceChoice"),entry.choice);
					App::Property::GetBool(list.get(),id("requireAvatar"),entry.requireAvatar);
					App::Property::GetArrayUInt32(list.get(),id("modes"),entry.modes_size,entry.modes);
					overrides.emplace(ID,entry);
				}
			}
		}
	}
	
}

cAnimationOverrideManager* cAnimationOverrideManager::Get() {
	if (ptr == nullptr) {
		ptr = new cAnimationOverrideManager();
	}
	return ptr;
}


void cAnimationOverrideManager::Dispose() {
	ptr = nullptr;
}


// For internal use, do not modify.
int cAnimationOverrideManager::AddRef()
{
	return DefaultRefCounted::AddRef();
}

// For internal use, do not modify.
int cAnimationOverrideManager::Release()
{
	return DefaultRefCounted::Release();
}

// You can extend this function to return any other types your class implements.
void* cAnimationOverrideManager::Cast(uint32_t type) const
{
	CLASS_CAST(Object);
	CLASS_CAST(cAnimationOverrideManager);
	return nullptr;
}
