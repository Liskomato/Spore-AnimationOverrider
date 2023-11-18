#pragma once

#include <Spore\BasicIncludes.h>

#define cAnimationOverrideManagerPtr intrusive_ptr<cAnimationOverrideManager>
#define AnimationOverrideManager (*cAnimationOverrideManager::Get())

class cAnimationOverrideManager 
	: public Object
	, public DefaultRefCounted
{
public:
	static const uint32_t TYPE = id("cAnimationOverrideManager");
	
	hash_map<uint32_t, AnimationOverride> overrides;

	void ReadProperties();
	
	~cAnimationOverrideManager();

	static cAnimationOverrideManager* Get();

	int AddRef() override;
	int Release() override;
	void* Cast(uint32_t type) const override;

	void Dispose();
private:
	static cAnimationOverrideManager* ptr;
	cAnimationOverrideManager();
};

struct AnimationOverride {
	uint32_t newID;			  // ID that we will override the old value with.
	uint32_t* modes;	      // Array of game mode IDs override will activate in.
	size_t modes_size;        // Size of game mode ID array
	bool requireAvatar = false;       // Require avatar for the override
	int choice = -1;    // animation ID choice.
};