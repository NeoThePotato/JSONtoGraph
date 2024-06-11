#include <stdexcept>

#pragma once
namespace Collections
{
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

        void Resize()
        {
            Resize(_capacity * GROWTH_COEFFICIENT);
        }

        void Resize(size_t newSize)
        {
            _capacity *= newSize;
            _length = size > _capacity ? _capacity : _length;
            T* temp = new T[_capacity];
            CopyTo(temp);
            delete[] _internalArray;
            _internalArray = temp;
        }

        void SetLength(size_t newLength)
        {
            if (newLength > _capacity)
                Resize(newLength);
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
            _capacity = other._capacity;
            _internalArray = new T[_capacity];
            _length = other._length;
            other->CopyTo(_internalArray);
        }

        ~DynamicArray()
        {
            delete[] _internalArray;
        }

        void Append(T element)
        {
            if (_length == _capacity)
                Resize();
            _internalArray[_length] = element;
            _length++;
        }

        void Remove(size_t pos)
        {
            if ((pos > _length) || (pos < START_INDEX))
            {
                throw std::out_of_range("Index out of range.");
                return;
            }

            for (size_t i = pos; i <= _length; i++)
                _internalArray[i] = _internalArray[i + INDEX_SHIFT];
            _length--;
        }

        void Insert(T element, size_t pos)
        {
            if ((pos > _length) || (pos < START_INDEX))
            {
                throw std::out_of_range("Index out of range.");
                return;
            }
            if (_length == _capacity)
                Resize();

            _length++;

            for (size_t i = _length - INDEX_SHIFT; i >= pos; i--)
            {
                if (i == pos)
                    _internalArray[i] = element;
                else
                    _internalArray[i] = _internalArray[i - INDEX_SHIFT];
            }
        }

        void Clear() {
            _length = 0;
        }

        size_t Length() const
        {
            return _length;
        }

        bool Empty() const
        {
            return Length() <= 0;
        }

        T Get(size_t index) const
        {
            return _internalArray[index];
        }

        T* ToArray() const
        {
            T* arr = new T[_length];
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
            for (size_t i = START_INDEX; i < _length; i++)
                _internalArray[i] = val;
        }
    };
}
