#include <stdexcept>

#pragma once

namespace Collections
{
	constexpr size_t HEAD_INDEX = 0;

	template <class T>
	class LinkedList
	{
	private:
		struct Node
		{
			Node* next;
			T val;

			~Node()
			{
				if (next != nullptr)
					delete next;
			}
		};

		Node* _head;
		size_t _size;

		Node* GetLast() const
		{
			Node* current = _head;
			if (current != nullptr)
			{
				while (current->next != nullptr)
				{
					current = current->next;
				}
			}
			return current;
		}

		Node* GetNode(size_t index) const
		{
			if (index >= _size)
				throw std::out_of_range("Index out of range.");
			Node* current = _head;
			for (size_t i = HEAD_INDEX; i < index; i++)
				current = current->next;
			return current;
		}

		Node* InsertAt(T val, Node* node)
		{
			Node* newNode = new Node();
			newNode->val = val;
			Node* nextNode = node->next;
			node->next = newNode;
			newNode->next = nextNode;
			_size++;
			return newNode;
		}

	public:
		~LinkedList()
		{
			delete _head;
		}

		void Insert(T val)
		{
			Node* last = GetLast();
			if (last == nullptr)
			{
				last = new Node();
				last->val = val;
				_head = last;
			}
			InsertAt(val, last);
		}

		void InsertAt(T val, size_t index)
		{
			if (_size == HEAD_INDEX)
				Insert(val);
			InsertAt(val, GetNode(index));
		}

		T Get(size_t index) const
		{
			return GetNode(index)->val;
		}

		size_t Count() const
		{
			return _size;
		}
	};
}
