#pragma once
#include "Sequence.h"

// record structure
template <typename T>
struct Item {
	T item;
	int priority;
};
//template <typename T>
//using ItemList = LinkedListSequence<T>;

template<typename T>
class PriorityQueue
{
public:
	// constructors --------------------------------------------------------
	PriorityQueue() {
		this->list = new LinkedListSequence<Item<T>>;
	}

	// functions -----------------------------------------------------------
	void Insert(T item, int priority) {
		Item<T> newItem = Item<T>();
		newItem.item = item;
		newItem.priority = priority;
		if (list->GetLength() == 0) {
			list->Append(newItem);
			return;
		}
		for (int i = 0; i < list->GetLength(); i++) {
			Item<T> currentItem = list->Get(i);
			if (priority >= currentItem.priority) {
				list->InsertAt(newItem, i);
				return;
			}
		}
		list->Append(newItem);
		return;
	}

	void IsEmpty() {
		return list->GetLength() == 0;
	}

	void Delete() {
		list->RemoveAt(0);
	}

	Item<T> GetHighestPriorityItem() {
		return list->GetFirst();
	}

	T GetHighestPriority() {
		return (list->GetFirst()).item;
	}

	Item<T> GetItem(const size_t index) {
		return this->list->Get(index);
	}

	size_t GetLength() {
		return this->list->GetLength();
	}

	// operators -----------------------------------------------------------
	Item<T> operator[](const size_t index) {
		return this->GetItem(index);
	}

	const Item<T> operator[](const size_t index) const {
		return this->GetItem(index);
	}

	~PriorityQueue() {
		delete[] this->list;
	}

private:
	LinkedListSequence<Item<T>>* list;
};
