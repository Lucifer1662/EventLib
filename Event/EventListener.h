#pragma once

//template <typename Return, typename... Args>
//class Event;

template<typename Return, typename... Args>
class EventListener {
	using Subscriber = Subscriber<Return, Args...>;
	//using Event = Event<Return, Args...>;
	const Subscriber& subscriber;
	//Event<Return, Args...>* event;

public:
	//EventListener(Event<Return, Args...>* event,const Subscriber& subscriber) :
	//	event(event),subscriber(subscriber) {}

	//template<typename Return, typename... Args>
	EventListener(const Subscriber& subscriber) :
		subscriber(subscriber) {}

	~EventListener();
};
