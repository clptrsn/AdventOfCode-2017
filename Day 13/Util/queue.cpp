#pragma once

template <class T>
struct QueueNode
{
	T data;
	QueueNode<T>* next;

	void initQueueNode(T newData)
	{
		data = newData;
		next = NULL;
	}
};

template <class T>
struct Queue
{
	QueueNode<T>* head;
	int len;

	void initQueue()
	 {
		head = NULL;
		len = 0;
	};

	void queueNode(T data)
	{
		QueueNode<T>* newNode = new QueueNode<T>;
		newNode->initQueueNode(data);

		newNode->next = head;

		len++;
		head = newNode;
	}

	T dequeueNode()
	{
		if(head == NULL)
		{
			return NULL;
		}
		else if(len == 1)
		{
			T result = head->data;
			head = NULL;
			len--;

			return result;
		}

		// We have at least two 
		QueueNode<T>* prev = NULL;
		QueueNode<T>* walk = head;
		while(walk->next != NULL)
		{
			prev = walk;
			walk = walk->next;
		}

		T result = walk->data;
		prev->next = NULL;
		len--;

		return result;
	}

	bool contains(T data)
	{
		QueueNode<T>* walk = head;
		while(walk != NULL && walk->data != data)
		{
			walk = walk->next;
		}

		if(walk != NULL)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};