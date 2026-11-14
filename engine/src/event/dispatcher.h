#pragma once
#include "event.h"

NS(ev)

class dispatcher {
public:
	dispatcher(event& event_) : _event(event_) {}

	template<typename T, typename F>
	bool dispatch(F&& func) {
		if (T::is_same(_event.type)) {
			_event.handled |= func(static_cast<T&>(_event));
			return true;
		}
		return false;
	}

private:
	event& _event;
};


END_NS