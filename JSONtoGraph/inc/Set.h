#pragma once
#include "DynamicArray.h";

namespace Collections
{
	template <class T>
	class Set : private DynamicArray<T>
	{
		bool Contains(T val, size_t* index) const
		{
			for (*index = START_INDEX; *index < Length(); (*index)++)
			{
				if (val == DynamicArray<T>::Get(*index))
					return true;
			}
			return false;
		}

	public:
		Set(size_t capacity = DEFAULT_CAPACITY) : DynamicArray<T>(capacity) { };

		bool TryAdd(T val)
		{
			if (!Contains(val))
			{
				DynamicArray<T>::Append(val);
				return true;
			}
			return false;
		}

		bool TryRemove(T val)
		{
			size_t index;
			if (Contains(val, &index))
			{
				DynamicArray<T>::Remove(index);
				return true;
			}
			return false;
		}

		size_t Length() const
		{
			return DynamicArray<T>::Length();
		}

		bool Contains(T val) const
		{
			size_t index;
			return Contains(val, &index);
		}
	};
}