#include "DynamicArray.h";

#pragma once
namespace Collections
{
	template <class T>
	class Queue
	{
		DynamicArray<T>* _internalArray;

	public:
		Queue(size_t capacity = DEFAULT_CAPACITY)
		{
			_internalArray = new DynamicArray<T>(capacity);
		}

		~Queue()
		{
			delete _internalArray;
		}

		void Enqueue(T val)
		{
			_internalArray->Insert(val, 0);
		}

		T Dequeue()
		{
			T val = _internalArray->Get(_internalArray->Length() - 1);
			_internalArray->Remove(_internalArray->Length() - 1);
			return val;
		}

		size_t Length() const
		{
			return _internalArray->Length();
		}

		bool Empty() const
		{
			return _internalArray->Empty();
		}
	};
}