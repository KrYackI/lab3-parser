#pragma once

template<typename T>
struct chain
{
	T value;
	chain* nextptr;
	chain(T val, chain* next = nullptr) : value(val), nextptr(next) {};
};