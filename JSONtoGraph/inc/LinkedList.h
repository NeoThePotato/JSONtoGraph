#pragma once
#include <stdexcept>

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
		size_t _length;

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
			if (index >= _length)
				throw std::out_of_range("Index out of range.");
			Node* current = _head;
			for (size_t i = HEAD_INDEX; i < index; i++)
				current = current->next;
			return current;
		}

		Node* InsertAfter(T val, Node* node)
		{
			Node* newNode = new Node();
			newNode->val = val;
			Node* nextNode = node->next;
			node->next = newNode;
			newNode->next = nextNode;
			_length++;
			return newNode;
		}

		Node* SetHead(T val)
		{
			Node* newNode = new Node();
			newNode->val = val;
			_head = newNode;
			_length++;
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
				SetHead(val);
			else
				InsertAfter(val, last);
		}

		void InsertAt(T val, size_t index)
		{
			if (_length == HEAD_INDEX)
				Insert(val);
			else
				InsertAfter(val, GetNode(index));
		}

		T Get(size_t index) const
		{
			return GetNode(index)->val;
		}

		size_t Count() const
		{
			return _length;
		}
	};
}
