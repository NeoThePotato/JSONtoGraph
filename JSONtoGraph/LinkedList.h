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

	void Insert(T val)
	{
		Node* last = GetLast();
		Node* newNode = new Node();
		newNode->val = val;
		last->next = newNode;
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
