#pragma once
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

