#include <iostream>
#include <string.h>
#include <stdio.h>
#include "redblack.h"
using namespace std;

Node::Node(char* id,char* fn,char* ln,char* a,char* s,int p){
    parent = left = right = NULL;
    color = RED;
    this->val = new char [strlen(id) + 1];
    strcpy(val,id);
    this->FName = new char [strlen(fn) + 1];
    strcpy(FName,fn);
    this->LName = new char [strlen(ln) + 1];
    strcpy(LName,ln);
    this->sex = new char [strlen(s) + 1];
    strcpy(sex,s);
    this->age = new char [strlen(a) + 1];
    strcpy(age,a);
    post_code=p;
    has_voted=false;

  }

Node *Node::uncle()
{
  // If no parent or grandparent, then no uncle
  if (parent == NULL or parent->parent == NULL)
    return NULL;

  if (parent->isOnLeft())
    // uncle on right
    return parent->parent->right;
  else
    // uncle on left
    return parent->parent->left;
}

bool Node::isOnLeft() { return this == parent->left; }

Node *Node::sibling()
{
  // sibling null if no parent
  if (parent == NULL)
    return NULL;

  if (isOnLeft())
    return parent->right;

  return parent->left;
}

void Node::moveDown(Node *nParent)
{
  if (parent != NULL)
  {
    if (isOnLeft())
    {
      parent->left = nParent;
    }
    else
    {
      parent->right = nParent;
    }
  }
  nParent->parent = parent;
  parent = nParent;
}

bool Node::hasRedChild()
{
  return (left != NULL and left->color == RED) or (right != NULL and right->color == RED);
}

void RBTree::leftRotate(Node *x)
{
  // new parent will be node's right child
  Node *nParent = x->right;

  // update root if current node is root
  if (x == root)
    root = nParent;

  x->moveDown(nParent);

  // connect x with new parent's left element
  x->right = nParent->left;
  // connect new parent's left element with node
  // if it is not null
  if (nParent->left != NULL)
    nParent->left->parent = x;

  // connect new parent with x
  nParent->left = x;
}

void RBTree::rightRotate(Node *x)
{
  // new parent will be node's left child
  Node *nParent = x->left;

  // update root if current node is root
  if (x == root)
    root = nParent;

  x->moveDown(nParent);

  // connect x with new parent's right element
  x->left = nParent->right;
  // connect new parent's right element with node
  // if it is not null
  if (nParent->right != NULL)
    nParent->right->parent = x;

  // connect new parent with x
  nParent->right = x;
}

void RBTree::swapColors(Node *x1, Node *x2)
{
  COLOR temp;
  temp = x1->color;
  x1->color = x2->color;
  x2->color = temp;
}

void RBTree::swapValues(Node *u, Node *v)
{
  char* temp;
  temp = u->val;
  u->val = v->val;
  v->val = temp;
}

void RBTree::fixRedRed(Node *x)
{
  // if x is root color it black and return
  if (x == root)
  {
    x->color = BLACK;
    return;
  }

  // initialize parent, grandparent, uncle
  Node *parent = x->parent, *grandparent = parent->parent;
  Node *uncle = x->uncle();

  if (parent->color != BLACK)
  {
    if (uncle != NULL && uncle->color == RED)
    {
      // uncle red, perform recoloring and recurse
      parent->color = BLACK;
      uncle->color = BLACK;
      grandparent->color = RED;
      fixRedRed(grandparent);
    }
    else
    {
      // Else perform LR, LL, RL, RR
      if (parent->isOnLeft())
      {
        if (x->isOnLeft())
        {
          // for left right
          swapColors(parent, grandparent);
        }
        else
        {
          leftRotate(parent);
          swapColors(x, grandparent);
        }
        // for left left and left right
        rightRotate(grandparent);
      }
      else
      {
        if (x->isOnLeft())
        {
          // for right left
          rightRotate(parent);
          swapColors(x, grandparent);
        }
        else
        {
          swapColors(parent, grandparent);
        }

        // for right right and right left
        leftRotate(grandparent);
      }
    }
  }
}

Node *RBTree::successor(Node *x) {
  Node *temp = x;

  while (temp->left != NULL)
    temp = temp->left;

  return temp;
}

Node *RBTree::BSTreplace(Node *x) {
  // when node have 2 children
  if (x->left != NULL && x->right != NULL)
    return successor(x->right);

  // when leaf
  if (x->left == NULL && x->right == NULL)
    return NULL;

  // when single child
  if (x->left != NULL)
    return x->left;
  else
    return x->right;
}

void RBTree::deleteNode(Node *v) {
  Node *u = BSTreplace(v);

  // True when u and v are both black
  bool uvBlack = ((u == NULL or u->color == BLACK) and (v->color == BLACK));
  Node *parent = v->parent;

  if (u == NULL) {
    // u is NULL therefore v is leaf
    if (v == root) {
      // v is root, making root null
      root = NULL;
    } else {
      if (uvBlack) {
        // u and v both black
        // v is leaf, fix double black at v
        fixDoubleBlack(v);
      } else {
        // u or v is red
        if (v->sibling() != NULL)
          // sibling is not null, make it red"
          v->sibling()->color = RED;
      }

      // delete v from the tree
      if (v->isOnLeft()) {
        parent->left = NULL;
      } else {
        parent->right = NULL;
      }
    }
    delete v->val;
    delete v->FName;
    delete v->LName;
    delete v->age;
    delete v->sex;
    delete v;
    return;
  }

  if (v->left == NULL or v->right == NULL) {
    // v has 1 child
    if (v == root) {
      // v is root, assign the value of u to v, and delete u
      v->val = u->val;
      v->left = v->right = NULL;
      delete u;
    } else {
      // Detach v from tree and move u up
      if (v->isOnLeft()) {
        parent->left = u;
      } else {
        parent->right = u;
      }
      delete v;
      u->parent = parent;
      if (uvBlack) {
        // u and v both black, fix double black at u
        fixDoubleBlack(u);
      } else {
        // u or v red, color u black
        u->color = BLACK;
      }
    }
    return;
  }

  // v has 2 children, swap values with successor and recurse
  swapValues(u, v);
  deleteNode(u);
}

void RBTree::fixDoubleBlack(Node *x) {
  if (x == root)
    // Reached root
    return;

  Node *sibling = x->sibling(), *parent = x->parent;
  if (sibling == NULL) {
    // No sibiling, double black pushed up
    fixDoubleBlack(parent);
  } else {
    if (sibling->color == RED) {
      // Sibling red
      parent->color = RED;
      sibling->color = BLACK;
      if (sibling->isOnLeft()) {
        // left case
        rightRotate(parent);
      } else {
        // right case
        leftRotate(parent);
      }
      fixDoubleBlack(x);
    } else {
      // Sibling black
      if (sibling->hasRedChild()) {
        // at least 1 red children
        if (sibling->left != NULL and sibling->left->color == RED) {
          if (sibling->isOnLeft()) {
            // left left
            sibling->left->color = sibling->color;
            sibling->color = parent->color;
            rightRotate(parent);
          } else {
            // right left
            sibling->left->color = parent->color;
            rightRotate(sibling);
            leftRotate(parent);
          }
        } else {
          if (sibling->isOnLeft()) {
            // left right
            sibling->right->color = parent->color;
            leftRotate(sibling);
            rightRotate(parent);
          } else {
            // right right
            sibling->right->color = sibling->color;
            sibling->color = parent->color;
            leftRotate(parent);
          }
        }
        parent->color = BLACK;
      } else {
        // 2 black children
        sibling->color = RED;
        if (parent->color == BLACK)
          fixDoubleBlack(parent);
        else
          parent->color = BLACK;
      }
    }
  }
}

Node *RBTree::search(char* n) {
  Node *temp = root;
  while (temp != NULL) {
    if (strcmp(n,temp->val)<0) {
      if (temp->left == NULL)
        break;
      else
        temp = temp->left;
    } else if (strcmp(n,temp->val)==0) {
      break;
    } else {
      if (temp->right == NULL)
        break;
      else
        temp = temp->right;
    }
  }
  return temp;
}

bool RBTree::search2(char* n) {
  Node *temp = root;
  while (temp != NULL) {
    if (strcmp(n,temp->val)<0) {
      if (temp->left == NULL)
        break;
      else
        temp = temp->left;
    } else if (strcmp(n,temp->val)==0) {
      break;
    } else {
      if (temp->right == NULL)
        break;
      else
        temp = temp->right;
    }
  }
  cout<<n<<endl;
  cout<<temp->val<<endl;
  if(strcmp(n,temp->val)==0)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

bool RBTree::insert(char* n,char* fn,char* ln,char* a,char* s,int pc) {
  Node *newNode = new Node(n,fn,ln,a,s,pc);
  if (root == NULL) {
    newNode->color = BLACK;
    root = newNode;
  } else {
    Node *temp = search(n);
    if (strcmp(temp->val,n)==0) {
        return 0;
    }
    // connect new node to correct node
    newNode->parent = temp;

    if (strcmp(n,temp->val)<0)
      temp->left = newNode;
    else
      temp->right = newNode;

    // fix red red voilaton if exists
    fixRedRed(newNode);
  }
  return 1;
}

bool RBTree::deleteByVal(char* n) {
  if (root == NULL)
    // Tree is empty
    return 0;

  Node *v = search(n);

  if (strcmp(v->val,n)!=0) {
    cout << "No node found to delete with value:" << n << endl;
    return 0;
  }
  deleteNode(v);
  return 1;
}


void RBTree::printInOrder(FILE* output) {
  if (root == NULL)
    cout << "Tree is empty" << endl;
  else
    inorder(root,output);
}

void RBTree::hasVoted(int* number_of_votes) {
  if (root == NULL)
    cout << "Tree is empty" << endl;
  else
    hasVotedHelp(root,number_of_votes);
  cout << endl;
}

void RBTree::hasVotedHelp(Node *x,int* number_of_votes) {
  if (x == NULL)
    return;
  hasVotedHelp(x->left,number_of_votes);
  if(x->has_voted==1){
    (*number_of_votes)++;
  }
  hasVotedHelp(x->right,number_of_votes);
}

void RBTree::hasVotedwPC(int* number_of_votes,int pc) {
  if (root == NULL)
    cout << "Tree is empty" << endl;
  else
    hasVotedwPCHelp(root,number_of_votes,pc);
  cout << endl;
}

void RBTree::hasVotedwPCHelp(Node *x,int* number_of_votes,int pc) {
  if (x == NULL)
    return;
  hasVotedwPCHelp(x->left,number_of_votes,pc);
  if(x->has_voted==1 && x->post_code==pc){
    (*number_of_votes)++;
  }
  hasVotedwPCHelp(x->right,number_of_votes,pc);
}

void RBTree::deletelist(){
    if (root == NULL)
      cout << "Tree is empty" << endl;
    else
      deletelistHelp(root);
    cout <<"Tree deleted!"<< endl;
}

void RBTree::deletelistHelp(Node *x) {
  if (x == NULL)
    return;
  deletelistHelp(x->left);
  delete x->val;
  delete x->FName;
  delete x->LName;
  delete x->age;
  delete x->sex;
  delete x;
  deletelistHelp(x->right);
}

void RBTree::inorder(Node *x,FILE* output) {
  if (x == NULL)
    return;
  inorder(x->left,output);
  printNode(x,output);
  inorder(x->right,output);
}

void RBTree::printNode(Node* x,FILE* output){
  fprintf(output,"%s %s %s %s %s %d %d\n",x->val,x->FName,x->LName,x->age,x->sex,x->post_code,x->has_voted);
}

void RBTree::showNode(Node* x){
  printf("%s %s %s %s %s %d %d\n",x->val,x->FName,x->LName,x->age,x->sex,x->post_code,x->has_voted);
}


void RBTree::vote(Node* here){
  here->has_voted=true;
  return;
}

void RBTree::renewBloom(BloomFilter *b){
  if (root == NULL)
      cout << "Tree is empty" << endl;
  else
      renewBloomHelp(b,root);
  cout <<"BF Renewed"<< endl;
}

void RBTree::renewBloomHelp(BloomFilter *b,Node* x){
  if (x == NULL)
  return;
  renewBloomHelp(b,x->left);
  b->add(x->val);
  renewBloomHelp(b,x->right);
}
