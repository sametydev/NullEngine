#pragma once

template<typename T>
class Singleton{
public:
	Singleton(void) = default;
	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;


	static T* instance(){
		static T inst{};

		return &inst;
	}
};