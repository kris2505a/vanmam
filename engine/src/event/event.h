#pragma once
#include "core/core.h"
#include "core/types/types.h"

#include "core/input/input_code.h"


NS(ev)

enum class event_type {
	key_down,
	key_up,
	button_down,
	button_up,
	mouse_move,
	mouse_scroll,
	quit
};

struct event {
	bool handled = false;
	event_type type;
	event(const event_type& type_) : type(type_) {}
};

struct key_press : event {
	key_code key;
	bool repeat;

	key_press(key_code key_, bool repeat_) : event(event_type::key_down), key(key_), repeat(repeat_) {}
	static bool is_same(event_type type) {
		return type == event_type::key_down;
	}
};

struct key_release : event {
	key_code key;

	key_release(key_code key_) : event(event_type::key_up), key(key_) {}
	static bool is_same(event_type type) {
		return type == event_type::key_up;
	}
};

struct button_press : event {
	button_code button;

	button_press(button_code button_) : event(event_type::button_down), button(button_) {}
	static bool is_same(event_type type) {
		return type == event_type::button_down;
	}
};

struct button_release : event {
	button_code button;

	button_release(button_code button_) : event(event_type::button_up), button(button_) {}
	static bool is_same(event_type type) {
		return type == event_type::button_up;
	}
};

struct mouse_move : event {
	f32 x;
	f32 y;

	mouse_move(f32 x_, f32 y_) : event(event_type::mouse_move), x(x_), y(y_) {}
	static bool is_same(event_type type) {
		return type == event_type::mouse_move;
	}
};

struct mouse_scroll : event {
	f32 x_offset;
	f32 y_offset;

	mouse_scroll(f32 x_offset_, f32 y_offset_) : event(event_type::mouse_scroll), x_offset(x_offset_), y_offset(y_offset_) {}
	static bool is_same(event_type type) {
		return type == event_type::mouse_scroll;
	}
};

struct quit : event {
	quit() : event(event_type::quit) {};
	static bool is_same(event_type type) {
		return type == event_type::quit;
	}
};

END_NS