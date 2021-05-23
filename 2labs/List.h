#ifndef LIST_H
#define LIST_H
#include <string>
using namespace std;
template<class T>
class list {
private:
	class nodeList;
	nodeList* head;
	int size;
public:
	list();
	~list();
	T pop();
	T pop(int);
	void push(T value);
	int getSize();
	void sort();
	string getString();

};

template <class T>
class list<T>::nodeList {
private:
	T value;
	nodeList* pNext;
public:
	nodeList() : pNext(nullptr) {};
	nodeList(T _value, nodeList* next) :
		value(_value), pNext(next) {}
	T getValue() {
		return value;
	}
	void setValue(T _value) {
		value = _value;
	}
	nodeList* getNext() {
		return pNext;
	}
	void setNext(nodeList* next) {
		pNext = next;
	}
};




template <class T>
list<T>::list() : head(nullptr), size(0) {}




template<class T>
list<T>::~list()
{
	while (size > 0)
		this->pop();
}



template <class T>
T list<T>::pop() {
	if (size == 0)
		return 0;
	if (size == 1) {
		T tempNextVal = head->getValue();
		delete head;
		head = nullptr;
		this->size = 0;
		return tempNextVal;
	}
	nodeList* temp = head;
	while (temp->getNext()->getNext() != nullptr) temp = temp->getNext();
	T tempNextVal = temp->getNext()->getValue();
	delete temp->getNext();
	size--;
	temp->setNext(nullptr);
	return tempNextVal;
}



template <class T>
T list<T>::pop(int index) {
	if (size == 1 || size == 0 || index == size - 1) {
		return this->pop();
	}
	if (index == 0) {
		nodeList* temp = head->getNext();
		T tempvalue = head->getValue();
		head = temp;
		size--;
		return tempvalue;
	}
	nodeList* temp = head;
	for (int i = 0; i < index - 1; i++)
		temp = temp->getNext();
	T tempNextVal = temp->getNext()->getValue();
	nodeList* tempNext = temp->getNext()->getNext();
	size--;
	temp->setNext(tempNext);
	return tempNextVal;
}



template <class T>
void list<T>::push(T value) {
	if (size == 0) {
		head = new nodeList(value, nullptr);
		size++;
		return;
	}
	nodeList* temp = head;
	while (temp->getNext() != nullptr) temp = temp->getNext();
	temp->setNext(new nodeList(value, nullptr));
	size++;
	return;
}



template <class T>
int list<T>::getSize() {
	return size;
}



template <class T>
void list<T>::sort() { 
	if (size == 1 || size == 0)
		return;
	nodeList* temp = head;
	bool f = false;
	for (int i = 0; i < size - 1; i++) {
		temp = head;
		f = false;
		for (int j = 0; j < size - 1 - i; j++) {
			if (temp->getValue()->getPower() > temp->getNext()->getValue()->getPower()) {
				T tempVal = temp->getValue();
				temp->setValue(temp->getNext()->getValue());
				temp->getNext()->setValue(tempVal);
				f = true;
			}
			temp = temp->getNext();
		}
		if (!f)
			return;
	}
}

template <class T>
string list<T>::getString() { 
	nodeList* temp = head;
	string out = "";
	while (temp != NULL) {
		out += temp->getValue() + '0';
		temp = temp->getNext();
	}
	return out;
}


#endif