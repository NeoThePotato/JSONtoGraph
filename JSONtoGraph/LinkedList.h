#pragma once
template <typename T>
class LinkedList
{
public:
	struct Node
	{
		Node* next;
		T val;
	};

private:
	Node* _head;

public:
	Node* Insert(T val)
	{
		Node* last = GetLast();
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
		while (current->next != nullptr)
		{
			current = current->next;
		}
		return current;
	}
};
