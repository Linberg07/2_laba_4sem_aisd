#ifndef HAFFMAN_H
#define HAFFMAN_H
#include <stdlib.h>
#include <string>
#include "list.h"
#include "queue.h"
#include "RBTree.h"
using namespace std;

class HaffmanTree {
private:
	class nodeHaffman {
	public:
		nodeHaffman* parent;
		nodeHaffman* pLeft;
		nodeHaffman* pRight;
		string code;

		char value;

		nodeHaffman(nodeHaffman* parent, nodeHaffman* left, nodeHaffman* right, char value) :
			parent(parent), pLeft(left), pRight(right), value(value), code("") {};

		void setParent(nodeHaffman* parent) {
			parent = parent;
		}

		void setCode(string code) {
			code = code;
		}

	};

	int power;
	nodeHaffman* root;

public:
	nodeHaffman* getRoot() {
		return root;
	}

	int getPower() {
		return power;
	}

	HaffmanTree(char value, int power) :
		power(power) {
		root = new nodeHaffman(nullptr, nullptr, nullptr, value);
	}

	HaffmanTree(HaffmanTree* leftTree, HaffmanTree* rightTree) {
		power = leftTree->getPower() + rightTree->getPower();
		root = new nodeHaffman(nullptr, leftTree->getRoot(), rightTree->getRoot(), NULL);
		root->pLeft->setParent(root);
		root->pRight->setParent(root);
	}

	void RLK(nodeHaffman* node)
	{
		if (node != nullptr)
		{
			if (node->pRight != nullptr) {
				node->pRight->code = node->code + "1";
				RLK(node->pRight);
			}
			if (node->pLeft != nullptr) {
				node->pLeft->code = node->code + "0";
				RLK(node->pLeft);
			}
		}
	}

	void toRbTree(RBTree<char, string>* tree, nodeHaffman* node)
	{
		if (node != nullptr)
		{
			if (node->pRight != nullptr) {
				toRbTree(tree, node->pRight);
			}
			if (node->pLeft != nullptr) {
				toRbTree(tree, node->pLeft);
			}
			if (node->value != 0)
				tree->insert(node->value, node->code);

		}
	}

	string decode(string encodeInput) {
		string out = "";
		nodeHaffman* node = root;
		for (int i = 0; i < encodeInput.length(); i++) {
			if (encodeInput[i] == '0')
				node = node->pLeft;
			else if (encodeInput[i] == '1')
				node = node->pRight;
			if (node->value != 0) {
				out += node->value;
				node = root;
			}
		}
		return out;
	}
};



#endif