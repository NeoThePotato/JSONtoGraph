#pragma once
template <typename T>
class LinkedList
{
public:
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

private:
	Node* _head;

public:
	~LinkedList()
	{
		delete _head;
	}

	Node* Insert(T val)
	{
		Node* last = GetLast();
		if (last == nullptr)
		{
			Node* newNode = new Node();
			newNode->val = val;
			_head = newNode;
			return _head;
		}
		return InsertAt(val, last);
	}

	Node* InsertAt(T val, Node* node)
	{
		Node* newNode = new Node();
		newNode->val = val;
		node->next = newNode;
		return newNode;
	}

	Node* GetLast()
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
};
