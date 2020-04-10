#include <iostream>
#include "bloom.h"
using namespace std;

enum COLOR { RED, BLACK };

class Node {
public:
  char * val;
  COLOR color;
  Node *left, *right, *parent;
  char * FName;
  char * LName;
  char * age;
  char * sex;
  int post_code;
  bool has_voted;

  Node(char*,char*,char*,char*,char*,int) ;
  Node *uncle();
  bool isOnLeft();// check if node is left child of parent
  Node *sibling();// returns pointer to sibling
  void moveDown(Node *);// moves node down and moves given node in its place
  bool hasRedChild();
};

class RBTree {
  Node *root;
  void leftRotate(Node *);// left rotates the given node
  void rightRotate(Node *);
  void swapColors(Node *, Node *);
  void swapValues(Node *, Node *);
  void fixRedRed(Node *); // fix red red at given node
  Node *successor(Node *);  // find node that do not have a left child in the subtree of the given node
  Node *BSTreplace(Node *); // find node that replaces a deleted node in BST
  void deleteNode(Node *); // deletes the given node
  void fixDoubleBlack(Node *);

public:

  RBTree() { root = NULL; }
  Node *getRoot() { return root; }
  Node *search(char*);// if not found returns the last node while traversing
  bool search2(char*);
  bool insert(char*,char*,char*,char*,char*,int);
  bool deleteByVal(char*);
  void printInOrder(FILE*);
  void inorder(Node *,FILE*);
  void printNode(Node*,FILE*);
  void showNode(Node*);
  void vote(Node*);
  void hasVoted(int*);
  void hasVotedHelp(Node *,int*);
  void hasVotedwPC(int*,int);
  void hasVotedwPCHelp(Node*,int*,int);
  void deletelist();
  void deletelistHelp(Node*);
  void renewBloom(BloomFilter*);
  void renewBloomHelp(BloomFilter*,Node* x);
};
