#pragma once
#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "Window.h"

class Events {
public:
	static bool* _keys;
	static unsigned int* _frames;
	static unsigned int _current;
	static float dx;
	static float dy;
	static float x;
	static float y;
	static bool _cursor_locked;
	static bool _cursor_started;

	static int init();
	static void pullEvents();
	static bool isPressed(int keycode);
	static bool justPressed(int keycode);
	static bool isClicked(int button);
	static bool justClicked(int button);
};

#endif // !EVENT_HANDLER_H