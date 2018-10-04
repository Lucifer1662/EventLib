
#include "Subscriber.h"
#include "EventListener.h"
#include <vector>

template<typename Return, typename... Args>
class Event {
	using Subscriber = Subscriber<Return, Args...>;
	using StaticFunc = Return(*)(Args...);
	
	std::vector<Subscriber> subscribers;

public:
	EventListener add(const Subscriber& subscriber) {
		subscribers.push_back(subscriber);
		return EventListener(*this, subscribers.back());
	}

	template<class T, Return(T::*MemberFunc)(Args...)>
	EventListener emplace_back(T& t) {
		subscribers.emplace_back(&t, Subscriber::function<T, MemberFunc>);
		return EventListener(*this, subscribers.back());
	}

	void operator()(Args... args) {
		for (auto& subscriber : subscribers)
			subscriber(args...);
	}

	template<typename T, Return(T::*MemberFunc)(Args...)>
	void remove(T& data) {
		for (int i = 0; i < subscribers.size();)
		{
			if (subscribers[i].getData() == &data &&
				subscribers[i].getObjectFunc() == &Subscriber::function<T, MemberFunc>) {
				subscribers[i] = subscribers.back();
				subscribers.pop_back();
			}
			else
				i++;
		}
	}

	void Event::remove(StaticFunc func) {
		for (int i = 0; i < subscribers.size();){
			if (subscribers[i].getStaticFunc() == func) {
				subscribers[i] = subscribers.back();
				subscribers.pop_back();
			}
			else
				i++;
		}
	}

	void Event::remove(const Subscriber& subscriber) {
		for (int i = 0; i < subscribers.size();){
			if (subscribers[i] == subscriber) {
				subscribers[i] = subscribers.back();
				subscribers.pop_back();
			}
			else
				i++;
		}
	}

};

