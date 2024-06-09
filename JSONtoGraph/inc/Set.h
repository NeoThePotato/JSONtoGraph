#include "DynamicArray.h";

#pragma once
namespace Collections
{
	template <class T>
	class Set
	{
		DynamicArray<T>* _internalArray;

		bool Contains(T val, size_t* index) const
		{
			for (*index = START_INDEX; *index < Length(); (*index)++)
			{
				if (val == _internalArray->Get(*index))
					return true;
			}
			return false;
		}

	public:
		Set(size_t capacity = DEFAULT_CAPACITY)
		{
			_internalArray = new DynamicArray<T>(capacity);
		}

		~Set()
		{
			delete _internalArray;
		}

		bool Add(T val)
		{
			if (!Contains(val))
			{
				_internalArray->Append(val);
				return true;
			}
			return false;
		}

		bool Remove(T val)
		{
			size_t index;
			if (Contains(val, &index))
			{
				_internalArray->Remove(index);
				return true;
			}
			return false;
		}

		size_t Length() const
		{
			return _internalArray->Length();
		}

		bool Contains(T val) const
		{
			size_t index;
			return Contains(val, &index);
		}
	};
}