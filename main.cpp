#include <iostream>
#include <cstring>
#include <fstream>
#include "Node.h"

using namespace std;

void add(Node* &treeRoot, Node* current, Node* newNode);
void print(Node* treeRoot, int level);
int correctInput();


int main() {
  Node* treeRoot = NULL;
  Node* current;
  Node* newNode;
  int level = 0;
  
  bool looping = true;
  while (looping == true) {
    int option = correctInput();
    // Add numbers to tree
    if (option == 1) {
      cout << "FILE or CONSOLE?" << endl;
      char input[15];
      cin.get(input, 15);
      cin.ignore(15, '\n');
      bool looping2 = true;
      while (looping2 == true) {
	// Add numbers through a file
	if (strcmp(input, "FILE") == 0) {
	  /*int input[100];
	  int totalNums;
	  cout << "How many numbers are you adding?" << endl;
	  cin >> totalNums;
	  cin.get();
	  // File input
	  ifstream numbers("testNumbers.txt");
	  for (int i = 0; i < totalNums; i++) {
	    numbers >> input[i];
	    Node* newNode = new Node(input[i]);
	    add(treeRoot, treeRoot, newNode);
	    }*/
	  looping2 = false;
	}
	// Add numbers through the console
	else if (strcmp(input, "CONSOLE") == 0) {
	  int input[100];
	  cout << "How many numbers would you like to add?" << endl;
	  int totalNums;
	  cin >> totalNums;
	  cin.get();
	  // Console input
	  cout << "Please enter your numbers." << endl;
	  for (int i = 0; i < totalNums; i++) {
	    cin >> input[i];
	    cin.get();
	    Node* newNode = new Node(input[i]);
	    add(treeRoot, treeRoot, newNode);
	  }
	  looping2 = false;
	}
	else {
	  cout << "Please input one of the two options" << endl;
	}
      }
    }
    // Print tree
    else if (option == 2) {
      print(treeRoot, level);
    }
    // Quit the program
    else if (option == 3) {
      looping = false;
    }
  }
}

int correctInput() {
  bool leaveLoop = false;
  cout << "Enter one of the following options: ADD, PRINT, or QUIT (uppercase)" << endl;
  while (leaveLoop == false) {
    char input[15];
    cin.get(input, 15);
    cin.ignore(15, '\n');
    if (strcmp(input, "ADD") == 0) {
      return 1;
    }
    else if (strcmp(input, "PRINT") == 0) {
      return 2;
    }
    else if (strcmp(input, "QUIT") == 0) {
      return 3;
    }
    else {
      cout << "Please enter a valid option." << endl;
    }
  }
  return -1;
}

void add(Node* &treeRoot, Node* current, Node* newNode) {
  if (newNode->getParent() == NULL) {
    if (treeRoot == NULL) {
      treeRoot = newNode;
      newNode->setParent(treeRoot);
    }
    // Add to the left
    else if (current->getNum() > newNode->getNum()) {
      if (current->getLeft() == NULL) {
	current->setLeft(newNode);
	newNode->setParent(current);
      }
      else if (current->getLeft() != NULL) {
	add(treeRoot, current->getLeft(), newNode);
      }
    }
    // Add to the right
    else if ((current->getNum() < newNode->getNum()) || (current->getNum() == newNode->getNum())) {
      if (current->getRight() == NULL) {
	current->setRight(newNode);
	newNode->setParent(current);
      }
      else if (current->getRight() != NULL) {
	add(treeRoot, current->getRight(), newNode);
      }
    }
  }  // Fix the tree
  if (newNode->getParent() != NULL) {
    cout << "fixing tree now" << endl;
    // Case 1: Insert at root
    if (treeRoot == newNode) {
      treeRoot->setColor('B');
    }
    // Case 3: Parent and uncle are red
    else if (newNode->getUncle() != NULL) {
      if (newNode->getParent()->getColor() == 'R' && newNode->getUncle()->getColor() == 'R') {
	cout << "what" << endl;
	newNode->getParent()->setColor('B');
	newNode->getUncle()->setColor('B');
	newNode->getParent()->getParent()->setColor('R');
	add(treeRoot, current, newNode->getParent()->getParent());
      }
    }
    // Case 4 & 5: Uncle is black, triangle case and line case
    // Triangle case
    else if (newNode->getUncle() == NULL || newNode->getUncle()->getColor() == 'B') {
      // Parent is left and node is right
      if (newNode->getParent()->getParent()->getLeft() == newNode->getParent() && newNode->getParent()->getRight() == newNode) {
	Node* tempParent = newNode->getParent();
	newNode->setParent(newNode->getParent()->getParent());
	newNode->getParent()->setLeft(newNode);
	Node* tempLeft = newNode->getLeft();
	newNode->setLeft(tempParent);
	tempParent->setParent(newNode);
	if (tempLeft != NULL) {
	  tempParent->setRight(tempLeft);
	  tempLeft->setParent(tempParent);
	}
      }
      // Parent is right and node is left
      else if (newNode->getParent()->getParent()->getRight() == newNode->getParent() && newNode->getParent()->getLeft() == newNode) {
	Node* tempParent = newNode->getParent();
	newNode->setParent(newNode->getParent()->getParent());
	newNode->getParent()->setRight(newNode);
	Node* tempRight = newNode->getRight();
	newNode->setRight(tempParent);
	tempParent->setParent(newNode);
	if (tempRight != NULL) {
	  tempParent->setRight(tempRight);
	  tempRight->setParent(tempParent);
	}
      }
      // Line case
      // Parent is left and node is left
      else if (newNode->getParent()->getParent()->getLeft() == newNode->getParent() && newNode->getParent()->getLeft() == newNode) {
	// Tree rotation
	Node* tempParent = newNode->getParent();
	Node* tempGrandParent = newNode->getParent()->getParent();
	// Change parents
	if (tempGrandParent->getParent() != NULL) {
	  newNode->getParent()->setParent(tempGrandParent->getParent());
	}
	else if (tempGrandParent->getParent() == NULL) {
	  cout << "root" << endl;
	  newNode->getParent()->setParent(NULL);
	  // treeRoot = newNode->getParent();
	}
	newNode->getParent()->setRight(tempParent->getParent()->getParent());
	// Change children
	if (tempParent->getRight() != NULL) {
	  newNode->getParent()->getRight()->setLeft(tempParent->getRight());
	}
	else {
	  newNode->getParent()->getRight()->setLeft(NULL);
	}
	// Swap colors
	if (newNode->getParent()->getColor() == 'R') {
	  newNode->getParent()->setColor('B');
	  newNode->getParent()->getRight()->setColor('R');
	}
	else if (newNode->getParent()->getColor() == 'B') {
	  if (newNode->getParent()->getRight()->getColor() == 'R') {
	    newNode->getParent()->setColor('R');
	    newNode->getParent()->getRight()->setColor('B');
	  }
	}
      }
      // Parent is right and node is right
      else if (newNode->getParent()->getParent()->getRight() == newNode->getParent() && newNode->getParent()->getRight() == newNode) {
	Node* tempParent = newNode->getParent();
	newNode->getParent()->setLeft(newNode->getParent()->getParent());
        if (newNode->getParent()->getLeft()->getParent() != NULL) {
	  newNode->getParent()->setParent(newNode->getParent()->getLeft()->getParent());
	}
	else {
	  newNode->getParent()->setParent(NULL);
	  treeRoot = newNode->getParent();
	}
	if (tempParent->getLeft() != NULL) {
	  newNode->getParent()->getLeft()->setRight(tempParent->getLeft());
	}
	else {
	  newNode->getParent()->getLeft()->setRight(NULL);
	}
	// Swap colors
	if (newNode->getParent()->getColor() == 'R') {
	  newNode->getParent()->setColor('B');
	  newNode->getParent()->getLeft()->setColor('R');
	}
	else if (newNode->getParent()->getColor() == 'B') {
	  if (newNode->getParent()->getLeft()->getColor() == 'R') {
	    newNode->getParent()->setColor('R');
	    newNode->getParent()->getLeft()->setColor('B');
	  }
	}
      }
    }
  }
}

void print(Node* treeRoot, int level) {
  if (treeRoot == NULL) {
    cout << "The tree is empty!" << endl << endl;
  }
  // Go through the right side of tree, finding where the tree stops, and indenting appropriately
  else {
    if (treeRoot->getRight() != NULL) {
      print(treeRoot->getRight(), level + 1);
    }
    // Indent values
    for (int i = 0; i < level; i++) {
      cout << '\t';
    }
    // Left side
    cout << treeRoot->getColor() << treeRoot->getNum() << endl;
    if (treeRoot->getLeft() != NULL) {
      print(treeRoot->getLeft(), level + 1);
    }
  }
}
