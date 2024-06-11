#pragma once
#include <stdexcept>

namespace Collections
{
    constexpr size_t EMPTY_ARRAY = 0;
    constexpr size_t START_INDEX = 0;
    constexpr size_t INDEX_SHIFT = 1;
    constexpr size_t DEFAULT_CAPACITY = 5;
    constexpr size_t GROWTH_COEFFICIENT = 2;

    template <class T>
    class DynamicArray
    {
    private:
        T* _internalArray;
        size_t _length;
        size_t _capacity;

        void EnsureCapacity(size_t neededCapacity)
        {
            if (neededCapacity <= _capacity)
                return;
            while (_capacity < neededCapacity)
                _capacity *= GROWTH_COEFFICIENT;
            T* newArr = new T[_capacity];
            CopyTo(newArr);
            delete[] _internalArray;
            _internalArray = newArr;
        }

        void SetLength(size_t newLength)
        {
            if (newLength > _capacity)
                EnsureCapacity(newLength);
            _length = newLength;
        }

        void CopyTo(T* target) const
        {
            for (size_t i = START_INDEX; i < _length; i++)
                target[i] = _internalArray[i];
        }

    public:
        DynamicArray(size_t capacity = DEFAULT_CAPACITY)
        {
            _capacity = capacity;
            _internalArray = new T[_capacity];
            _length = START_INDEX;
        }

        DynamicArray(const DynamicArray<T>* other)
        {
            _capacity = other->_capacity;
            _internalArray = new T[_capacity];
            _length = other->Length();
            other->CopyTo(_internalArray);
        }

        ~DynamicArray()
        {
            delete[] _internalArray;
        }

        void Append(T element)
        {
            SetLength(_length + INDEX_SHIFT);
            _internalArray[Length() - INDEX_SHIFT] = element;
        }

        void Remove(size_t index)
        {
            if ((index > Length()) || (index < START_INDEX))
                throw std::out_of_range("Index out of range.");

            for (size_t i = index; i <= Length(); i++)
                _internalArray[i] = _internalArray[i + INDEX_SHIFT];
            _length--;
        }

        void Insert(T element, size_t index)
        {
            if ((index > Length()) || (index < START_INDEX))
                throw std::out_of_range("Index out of range.");
            size_t newLength = index < Length() ? _length : index;
            newLength += INDEX_SHIFT;
            SetLength(newLength);

            // Shift Right
            if (Length() > 1)
            {
                for (size_t i = Length() - INDEX_SHIFT; i > index; i--)
                    _internalArray[i] = _internalArray[i - INDEX_SHIFT];
            }
            _internalArray[index] = element;
            _length = newLength;
        }

        void Clear() {
            SetLength(EMPTY_ARRAY);
        }

        size_t Length() const
        {
            return _length;
        }

        bool Empty() const
        {
            return Length() <= EMPTY_ARRAY;
        }

        T Get(size_t index) const
        {
            if ((index > _length) || (index < START_INDEX))
                throw std::out_of_range("Index out of range.");
            return _internalArray[index];
        }

        void Set(T element, size_t index)
        {
            if (index < START_INDEX)
                throw std::out_of_range("Index out of range.");
            if (index >= Length())
                SetLength(index + INDEX_SHIFT);
            _internalArray[index] = element;
        }

        T* ToArray() const
        {
            T* arr = new T[Length()];
            CopyTo(arr);
            return arr;
        }

        void SetAll(T val, size_t length)
        {
            SetLength(length);
            SetAll(val);
        }

        void SetAll(T val)
        {
            for (size_t i = START_INDEX; i < Length(); i++)
                _internalArray[i] = val;
        }
    };
}
