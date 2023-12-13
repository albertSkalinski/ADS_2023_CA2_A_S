#pragma once

template <class T>
class DListNode
{
public:
	T data;
	DListNode<T>* next;
	DListNode<T>* previous;

	DListNode(T item);
	DListNode(DListNode<T>& item);
	void insertBefore(T item);
	void insertAfter(T item);

	~DListNode()
	{
		//next = nullptr;
		//previous = nullptr;
	}
};


template <class T>
DListNode<T>::DListNode(DListNode<T>& node)
{
	this->data = new DListNode(node->data);
}
template <class T>
DListNode<T>::DListNode(T item)
{
	data = item;
	next = previous = nullptr;
}

template <class T>
void DListNode<T>::insertAfter(T item)
{
	DListNode<T>* N = new DListNode(item);
	N->previous = this;
	N->next = this->next;
	this->next = N;
	if (N->next != nullptr)
		N->next->previous = N;
}

template <class T>
void DListNode<T>::insertBefore(T item)
{
	DListNode<T>* N = new DListNode(item);
	N->next = this;
	N->previous = this->previous;
	this->previous = N;
	if (N->previous != nullptr)
		N->previous->next = N;
}
