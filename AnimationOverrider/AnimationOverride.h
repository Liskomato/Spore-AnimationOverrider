#pragma once

struct AnimationOverride {
	uint32_t newID;			  // ID that we will override the old value with.
	uint32_t* modes;	      // Array of game mode IDs override will activate in.
	size_t modes_size;        // Size of game mode ID array
	bool requireAvatar = false;       // Require avatar for the override
	int choice = -1;    // animation ID choice.
};