#include "list.h"
#include "queue.h"
#include "RBTree.h"
#include "HaffmanTree.h"
#include <string>
#include <iostream>

using namespace std;


string to_binary_string(char n)
{
	string result;
	do
	{
		result += ('0' + (n % 2));
		n = n / 2;
	} while (n > 0);
	return result;
}



int main() {
	string input;
	list<HaffmanTree*> listOfHaffmanTrees;
	RBTree<char, int> rbtree; 
	cin >> input;
	int tempVal;
	for (int i = 0; i < input.length(); i++) {
		if (rbtree.find(input[i]) == 0) {
			rbtree.insert(input[i], 1);
		}
		else {
			tempVal = rbtree.find(input[i]);
			rbtree.remove(input[i]);
			rbtree.insert(input[i], tempVal + 1);
		}
	}
	RBTree<char, int>::iterator it(&rbtree);
	++it;
	cout << "symbol rate: \n";
	for (int i = 0; i < rbtree.getSize(); i++) {
		listOfHaffmanTrees.push(new HaffmanTree(*it, it.getValue()));
		cout << *it << " " << it.getValue() << endl;
		++it;
	}
	while (listOfHaffmanTrees.getSize() != 1) {
		listOfHaffmanTrees.sort();
		listOfHaffmanTrees.push(new HaffmanTree(listOfHaffmanTrees.pop(0), listOfHaffmanTrees.pop(1)));
	}

	HaffmanTree* haffmanTree = listOfHaffmanTrees.pop(0);
	

	cout << "First string: ";
	for (int i = 0; i < input.length(); i++) {
		for (int j = 0; j < (8 - to_binary_string(input[i]).length()); j++)
			cout << "0";
		cout << to_binary_string(input[i]) + " ";
	}

	haffmanTree->RLK(haffmanTree->getRoot());

	RBTree<char, string> haffmanTable;
	haffmanTree->toRbTree(&haffmanTable, haffmanTree->getRoot());

	cout << "\n\nstring weight: " << 8 * input.length() << " bits";


	string encodeInput = "";
	cout << "\n\nSecond string: ";
	for (int i = 0; i < input.length(); i++) {
		encodeInput += haffmanTable.find(input[i]);
		cout << haffmanTable.find(input[i]);
		cout << " ";
	}

	cout << "\n\nencode weight: " << encodeInput.length() << " bits";

	
	cout << "\n\nDecode string: ";
	cout << haffmanTree->decode(encodeInput);


	
	cout << "\n\nCompression ratio: ";
	cout << (float(encodeInput.length()) / float((8 * input.length()))) * 100 << " %\n";

	return 0;
}