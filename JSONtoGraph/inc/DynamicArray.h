#include <stdexcept>

#pragma once
namespace Collections
{
    constexpr size_t START_INDEX = 0;
    constexpr size_t INDEX_SHIFT = 1;
    constexpr size_t DEFAULT_CAPACITY = 1;
    constexpr size_t GROWTH_COEFFICIENT = 2;

    template <class T>
    class DynamicArray
    {
    private:
        T* _internalArray;
        size_t _size;
        size_t _capacity;

        void Resize()
        {
            _capacity *= GROWTH_COEFFICIENT;
            T* temp = new T[_capacity];
            CopyTo(temp);
            delete[] _internalArray;
            _internalArray = temp;
        }

    public:
        DynamicArray(size_t capacity = DEFAULT_CAPACITY)
        {
            _capacity = capacity;
            _internalArray = new T[_capacity];
            _size = START_INDEX;
        }

        ~DynamicArray()
        {
            delete[] _internalArray;
        }

        void Append(T element)
        {
            if (_size == _capacity)
                Resize();
            _internalArray[_size] = element;
            _size++;

        }

        void Remove(size_t pos)
        {
            if ((pos > _size) || (pos < START_INDEX))
            {
                throw std::out_of_range("Index out of range.");
                return;
            }

            for (size_t i = pos; i <= _size; i++)
                _internalArray[i] = _internalArray[i + INDEX_SHIFT];
            _size--;
        }

        void Insert(T element, size_t pos)
        {
            if ((pos > _size) || (pos < START_INDEX))
            {
                throw std::out_of_range("Index out of range.");
                return;
            }
            if (_size == _capacity)
                Resize();

            _size++;

            for (size_t i = _size - INDEX_SHIFT; i >= pos; i--)
            {
                if (i == pos)
                    _internalArray[i] = element;
                else
                    _internalArray[i] = _internalArray[i - INDEX_SHIFT];
            }
        }

        void CopyTo(T* target) const
        {
            for (size_t i = START_INDEX; i < _size; i++)
                target[i] = _internalArray[i];
        }

        size_t Length() const
        {
            return _size;
        }

        T Get(size_t index) const
        {
            return _internalArray[index];
        }

        T* ToArray() const
        {
            T* arr = new T[_size];
            CopyTo(arr);
            return arr;
        }
    };
}
