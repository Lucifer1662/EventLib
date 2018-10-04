#include "EventListener.h"


template<typename Return, typename... Args>
EventListener<Return, Args...>::~EventListener() {
	std::cout << "Event Listener Destroyed" << std::endl;
	//event->remove(subscriber);
}

