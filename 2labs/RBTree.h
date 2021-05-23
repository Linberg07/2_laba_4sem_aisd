#include <iostream>
#include <string>
#include "queue.h"
#include "list.h"

using namespace std;

template <class T_key, class T_value>
class RBTree {
	class Node;

protected:
	Node* nil;
	Node* root;

private:
	enum class Color {
		Black,
		Red
	};
	class Node {
	public:
		Color color;
		T_key key;
		Node* pLeft;
		Node* pRight;
		Node* parent;
		T_value value;

		Node() : color(Color::Black), key(0),
			pLeft(nullptr), pRight(nullptr),
			parent(nullptr) {}


		Node(Node* node) : color(node->color), key(node->key),
			pLeft(node->pLeft), pRight(node->pRight),
			parent(node->parent), value(node->value) {}


		Node(Color _color, T_key _key, Node* left, Node* right, Node* _parent, T_value _value) :
			color(_color), key(_key),
			pLeft(left), pRight(right),
			parent(_parent), value(_value) {}

	};



	void leftRotate(Node* x) {
		Node* y = x->pRight;
		x->pRight = y->pLeft;

		if (y->pLeft != nil)
			y->pLeft->parent = x;

		if (y != nil)
			y->parent = x->parent;

		if (x->parent == nil)
			root = y;
		else if (x == x->parent->pLeft)
			x->parent->pLeft = y;
		else
			x->parent->pRight = y;

		y->pLeft = x;
		if (x != nil)
			x->parent = y;
	}



	void rightRotate(Node* y) {
		Node* x = y->pLeft;
		y->pLeft = x->pRight;

		if (x->pRight != nil)
			x->pRight->parent = y;

		if (x != nil)
			x->parent = y->parent;

		if (y->parent == nil)
			root = x;
		else if (y == y->parent->pRight)
			y->parent->pRight = x;
		else
			y->parent->pLeft = x;

		x->pRight = y;
		if (y != nil)
			y->parent = x;
	}



	void rbInsertFixup(Node* z) {
		while (z != root && z->parent->color == Color::Red) {
			if (z->parent == z->parent->parent->pLeft) {
				Node* y = z->parent->parent->pRight;
				if (y->color == Color::Red) {
					z->parent->color = Color::Black;
					y->color = Color::Black;
					z->parent->parent->color = Color::Red;
					z = z->parent->parent;
				}
				else {
					if (z == z->parent->pRight) {
						z = z->parent;
						leftRotate(z);
					}
					z->parent->color = Color::Black;
					z->parent->parent->color = Color::Red;
					rightRotate(z->parent->parent);
				}
			}
			else {
				Node* y = z->parent->parent->pLeft;
				if (y->color == Color::Red) {
					z->parent->color = Color::Black;
					y->color = Color::Black;
					z->parent->parent->color = Color::Red;
					z = z->parent->parent;
				}
				else {
					if (z == z->parent->pLeft) {
						z = z->parent;
						rightRotate(z);
					}
					z->parent->color = Color::Black;
					z->parent->parent->color = Color::Red;
					leftRotate(z->parent->parent);
				}
			}
		}
		root->color = Color::Black;
	}



	void rbInsert(Node* z) {
		Node* y = nil;
		Node* x = root;

		while (x != nil) {
			y = x;
			if (z->key < x->key)
				x = x->pLeft;
			else
				x = x->pRight;
		}

		z->parent = y;

		if (y == nil)
			root = z;
		else if (z->key < y->key)
			y->pLeft = z;
		else
			y->pRight = z;

		z->pLeft = nil;
		z->pRight = nil;
		z->color = Color::Red;
		rbInsertFixup(z);
	}



	void deleteFixup(Node* x) {
		while (x != root && x->color == Color::Black) {
			if (x == x->parent->pLeft) {
				Node* w = x->parent->pRight;
				if (w->color == Color::Red) {
					w->color = Color::Black;
					x->parent->color = Color::Red;
					leftRotate(x->parent);
					w = x->parent->pRight;
				}
				if (w->pLeft->color == Color::Black && w->pRight->color == Color::Black) {
					w->color = Color::Red;
					x = x->parent;
				}
				else {
					if (w->pRight->color == Color::Black) {
						w->pLeft->color = Color::Black;
						w->color = Color::Red;
						rightRotate(w);
						w = x->parent->pRight;
					}
					w->color = x->parent->color;
					x->parent->color = Color::Black;
					w->pRight->color = Color::Black;
					leftRotate(x->parent);
					x = root;
				}
			}
			else {
				Node* w = x->parent->pLeft;
				if (w->color == Color::Red) {
					w->color = Color::Black;
					x->parent->color = Color::Red;
					rightRotate(x->parent);
					w = x->parent->pLeft;
				}
				if (w->pRight->color == Color::Black && w->pLeft->color == Color::Black) {
					w->color = Color::Red;
					x = x->parent;
				}
				else {
					if (w->pLeft->color == Color::Black) {
						w->pRight->color = Color::Black;
						w->color = Color::Red;
						leftRotate(w);
						w = x->parent->pLeft;
					}
					w->color = x->parent->color;
					x->parent->color = Color::Black;
					w->pLeft->color = Color::Black;
					rightRotate(x->parent);
					x = root;
				}
			}
		}
		x->color = Color::Black;
	}



	void deleteNode(Node* z) {
		Node* x, * y;

		if (z == nil)
			return;

		if (z->pLeft == nil || z->pRight == nil)
			y = z;
		else {
			y = z->pRight;
			while (y->pLeft != nil) y = y->pLeft;
		}

		if (y->pLeft != nil)
			x = y->pLeft;
		else
			x = y->pRight;

		x->parent = y->parent;
		if (y->parent != nil) {
			if (y == y->parent->pLeft)
				y->parent->pLeft = x;
			else
				y->parent->pRight = x;
		}
		else
			root = x;

		if (y != z) {
			z->key = y->key;
			z->value = y->value;
		}

		if (y->color == Color::Black)
			deleteFixup(x);

		delete y;
	}



	Node* findNode(T_key key) {
		Node* it = root;
		while (it->key != key && it != nil) {
			if (it->key < key)
				it = it->pRight;
			else
				it = it->pLeft;
		}
		if (it == nil)
			return(nullptr);
		return it;
	}



	void recursionForClear(Node* x) {
		if (x->PLeft != nil)
			recursionForClear(x->pLeft);
		if (x->pRight != nil)
			recursionForClear(x->pRight);
		delete x;

	}

public:

	class iterator : public RBTree {
	private:
		queue<Node*> queueIt;
		T_value value;
		T_key key;
		Node* it;
		Node* nil;
	public:

		iterator(RBTree* tree) : it(NULL),
			value(tree->root->value), key(tree->root->key), nil(tree->nil) {
			queueIt.push(tree->root);
		}

		const T_value& operator++() {
			if (queueIt.getSize() == 0)
				return NULL;
			it = queueIt.front();
			queueIt.pop();
			if (it->pLeft != nil)
				queueIt.push(it->pLeft);
			if (it->pRight != nil)
				queueIt.push(it->pRight);
			value = it->value;
			key = it->key;
			return it->value;
		}

		const T_key& operator*() {
			return key;
		}


		const T_value& getValue() {
			return value;
		}
	};



	RBTree() {
		nil = new Node();
		root = nil;
	}



	void insert(T_key _key, T_value _value) {
		Node* node = new Node(Color::Red, _key, nullptr, nullptr, nullptr, _value);
		rbInsert(node);
	}



	T_value find(T_key _key) {
		if (findNode(_key))
			return findNode(_key)->value;
		return 0;
	}



	void remove(T_key _key) {
		deleteNode(findNode(_key));
	}



	void clear() {
		recursionForClear(root);
		root = nil;
	}



	list<T_key> get_keys() {
		list<T_key> out;
		iterator it(this);
		while (++it != NULL) {
			out.push(*it);
		}
		return out;
	}



	list<T_value> get_values() {
		list<T_value> out;
		iterator it(this);
		while (++it != NULL) {
			out.push(it.getValue());
		}
		return out;
	}



	void print() {
		iterator it(this);
		cout << '\n';
		while (++it != NULL) {
			cout << *it << " ";
		}
	}

	int getSize() {
		int i = 0;
		iterator it(this);
		while (++it != NULL) {
			i++;
		}
		return i;
	}
};

#pragma once