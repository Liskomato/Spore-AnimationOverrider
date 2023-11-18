#pragma once

#include <Spore\BasicIncludes.h>
#include "AnimationOverride.h"

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
