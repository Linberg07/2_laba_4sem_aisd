#ifndef QUEUE_H
#define QUEUE_H
using namespace std;
template<class T>
class queue {
private:
	class nodeQueue;
	nodeQueue* head;
	nodeQueue* tail;
	int size;
public:
	queue();
	~queue();
	T pop();
	void push(T value);
	int getSize();
	T front();
};

template <class T>
class queue<T>::nodeQueue {
private:
	T value;
	nodeQueue* pNext;
public:
	nodeQueue() : pNext(nullptr) {};
	nodeQueue(T _value, nodeQueue* next) :
		value(_value), pNext(next) {}
	T getValue() {
		return value;
	}
	void setValue(T _value) {
		value = _value;
	}
	nodeQueue* getNext() {
		return pNext;
	}
	void setNext(nodeQueue* next) {
		pNext = next;
	}
};

template <class T>
queue<T>::queue() : head(nullptr), tail(nullptr), size(0) {}




template<class T>
queue<T>::~queue()
{
	while (size > 0)
		this->pop();
}



template <class T>
T queue<T>::pop() {
	if (size == 0)
		throw "queue error";
	nodeQueue* temp = head;
	T tempVal = head->getValue();
	head = head->getNext();
	delete temp;
	size--;
	if (head == nullptr)
		tail = head;
	return tempVal;
}



template <class T>
void queue<T>::push(T value) {
	if (size == 0) {
		head = new nodeQueue(value, nullptr);
		tail = head;
		size++;
		return;
	}
	tail->setNext(new nodeQueue(value, nullptr));
	tail = tail->getNext();
	size++;
	return;
}



template <class T>
int queue<T>::getSize() {
	return size;
}

template <class T>
T queue<T>::front() {
	return this->head->getValue();
}


#endif