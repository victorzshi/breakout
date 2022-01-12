#pragma once

#include <SDL.h>

class Timer
{
public:
	Timer();

	void start();

	// Returns time in milliseconds.
	Uint32 get_time();

private:
	Uint32 start_time;
};
