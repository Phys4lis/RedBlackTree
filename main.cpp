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
  if (newNode->getParent() != NULL) {
    if (treeRoot == newNode) {
      treeRoot->setColor('B');
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
