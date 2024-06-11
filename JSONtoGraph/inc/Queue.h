#pragma once
#include "DynamicArray.h";

namespace Collections
{
	template <class T>
	class Queue : private DynamicArray<T>
	{
	public:
		Queue(size_t capacity = DEFAULT_CAPACITY) : DynamicArray<T>(capacity) { };

		void Enqueue(T val)
		{
			DynamicArray<T>::Insert(val, START_INDEX);
		}

		T Dequeue()
		{
			T val = DynamicArray<T>::Get(DynamicArray<T>::Length() - INDEX_SHIFT);
			DynamicArray<T>::Remove(Length() - 1);
			return val;
		}

		size_t Length() const
		{
			return DynamicArray<T>::Length();
		}

		bool Empty() const
		{
			return DynamicArray<T>::Empty();
		}
	};
}