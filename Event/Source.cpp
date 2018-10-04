
#include <vector>
#include <iostream>

//#include "Event.h"

/*
template<typename Return, typename... Args>
class Subscriber {
	using Func = Return(*)(void*, Args...);
	using StaticFunc = Return(*)(Args...);
	union
	{
		struct {
			Func func;
			void* data;	
		};
		StaticFunc staticFunc;
	};


public:
	Subscriber(void* data, Func func) : data(data), func(func) {}
	Subscriber(StaticFunc staticFunc) : staticFunc(staticFunc) {}

	template<class T, Return(T::*MemberFunc)(Args...)>
	static Subscriber Create(T& data) {
		return Subscriber(&data, function<T, MemberFunc>);
	}

	template<class T, Return(T::*MemberFunc)(Args...)>
	static Return function(void* data, Args... args) {
		return (*(T*)data.*(MemberFunc))(args...);
	}

	template<class T, Return(T::*MemberFunc)(Args...)>
	void setCallback() {
		func = function<T, MemberFunc>;
	}

	void setCallback(StaticFunc staticFunc) {
		data = nullptr;
		this->staticFunc = staticFunc;
	}

	Return operator()(Args... args) {
		if (data != nullptr)
			func(data, args...);
		else
			staticFunc(args...);
	}

	bool operator ==(const Subscriber& subscriber) {
		return func == subscriber.func && data == subscriber.data;
	}

	void* getData() { return data; };
	Func getObjectFunc() { return func; };
	StaticFunc getStaticFunc() { return staticFunc; };
};



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

	void remove(StaticFunc func) {
		for (int i = 0; i < subscribers.size();)
		{
			if (subscribers[i].getStaticFunc() == func) {
				subscribers[i] = subscribers.back();
				subscribers.pop_back();
			}
			else
				i++;
		}
	}

	void remove(const Subscriber& subscriber) {
		for (int i = 0; i < subscribers.size();)
		{
			if (subscribers[i] == subscriber) {
				subscribers[i] = subscribers.back();
				subscribers.pop_back();
			}
			else
				i++;
		}
	}

};


*/



template<typename Return, typename... Args>
class Subscriber {
using Func = Return(*)(void*, Args...);
using StaticFunc = Return(*)(Args...);
union
{
struct {
Func func;
void* data;
};
StaticFunc staticFunc;
};


public:
Subscriber(void* data, Func func) : data(data), func(func) {}
Subscriber(StaticFunc staticFunc) : staticFunc(staticFunc) {}

template<class T, Return(T::*MemberFunc)(Args...)>
static Subscriber Create(T& data) {
return Subscriber(&data, function<T, MemberFunc>);
}

template<class T, Return(T::*MemberFunc)(Args...)>
static Return function(void* data, Args... args) {
return (*(T*)data.*(MemberFunc))(args...);
}

template<class T, Return(T::*MemberFunc)(Args...)>
void setCallback() {
func = function<T, MemberFunc>;
}

void setCallback(StaticFunc staticFunc) {
data = nullptr;
this->staticFunc = staticFunc;
}

Return operator()(Args... args) {
if (data != nullptr)
func(data, args...);
else
staticFunc(args...);
}

bool operator ==(const Subscriber& subscriber) {
return func == subscriber.func && data == subscriber.data;
}

void* getData() { return data; };
Func getObjectFunc() { return func; };
StaticFunc getStaticFunc() { return staticFunc; };
};



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

void remove(StaticFunc func) {
for (int i = 0; i < subscribers.size();)
{
if (subscribers[i].getStaticFunc() == func) {
subscribers[i] = subscribers.back();
subscribers.pop_back();
}
else
i++;
}
}

void remove(const Subscriber& subscriber) {
for (int i = 0; i < subscribers.size();)
{
if (subscribers[i] == subscriber) {
subscribers[i] = subscribers.back();
subscribers.pop_back();
}
else
i++;
}
}

};



struct A {
	int a=5, b, c;
	void notify(int i) {
		std::cout << &a;
		std::puts("      Notify A");
	}
};

struct B {
	int a = 5, b, c;
	void notify() { std::puts("B"); ;}
	void get(int i) { std::cout << "Get B " << i << std::endl; };
	void get1(int i) { std::cout << "Get B " << i << std::endl; };
};



void foo(int) {
	std::puts("foo");
}


void main() {


	
	B b;

	Event<void, int> event = Event<void, int>();
	auto blistener = event.emplace_back<B, &B::get1>(b);
	std::cout << &b << std::endl;
	{
		A a;
		auto alistener = event.emplace_back<A, &A::notify>(a);
		event(10);
		int y = 4;
	}
	int y = 5,t = 9;
	std::cout << &y << std::endl;
	int a[100];

	event(10);

	int p;
	std::cin >> p;
}