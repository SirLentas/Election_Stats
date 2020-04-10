#include <iostream>
#include <stdio.h>
#include "postlist.h"
#include <string.h>
using namespace std;


List::List(){head=NULL;};

List::~List(){
    delete head;
    cout<<"List deleted!"<<endl;
}

bool List::searchPostalCode(int key){
    PostList* sherlock;
    sherlock=head;
    if(sherlock==NULL)
        return 0;
    while(sherlock!=NULL){
        if(sherlock->postalCode==key)
            return 1;
        sherlock=sherlock->nextPC;
    }
    return 0;
}

PostList* List::returnPostList(int key){
    PostList* sherlock;
    sherlock=head;
    while(sherlock->postalCode!=key)
        sherlock=sherlock->nextPC;
    return sherlock;
}

void List::addInPostal(PostList* a,char* key){
    a->addPostListNode(key);
    (a->number_of_ids)++;
    return;
}

void List::addNewPostal(int key,char* vtr){
    PostList *newNode = new PostList();
    newNode->postalCode=key;
    newNode->first=NULL;
    newNode->nextPC=NULL;
    newNode->addPostListNode(vtr);
    (newNode->number_of_ids)++;
    if(head==NULL){
        head=newNode;
    }else{
        PostList* sherlock;
        sherlock=head;
        while(sherlock->nextPC!=NULL){
            sherlock=sherlock->nextPC;
        }
        sherlock->nextPC=newNode;
    }
    return;
}

void PostList::addPostListNode(char* data){
    PostListNode *newNode = new PostListNode();
    newNode->key = new char [strlen(data) + 1];
	strcpy(newNode->key,data);
    newNode->next=NULL;
    if(first==NULL){
        first=newNode;
    }else{
        PostListNode* sherlock;
        sherlock=first;
        while(sherlock->next!=NULL)
            sherlock=sherlock->next;
        sherlock->next=newNode;
    }
    return;
}

void List::print(){
    PostList* sherlock;
    sherlock=head;
    PostListNode* john;
    char* t;
    while(sherlock!=NULL){
        john=sherlock->first;
        while(john!=NULL){
            t=john->key;
            john=john->next;
        }
        sherlock=sherlock->nextPC;
    }
    return;
}

void List::deletefromList(char* data){
    PostList* sherlock;
    sherlock=head;
    PostListNode* john;
    while(sherlock!=NULL){
        john=sherlock->first;
        if(!strcmp(data,john->key)){
            sherlock->first=john->next;
            delete john;
        }
        while(john->next!=NULL){
            if(!strcmp(data,john->next->key)){
                PostListNode* temp;
                temp=john->next;
                john->next=john->next->next;
                delete temp;
            }
            if(john->next!=NULL)
                john=john->next;
        }
        sherlock=sherlock->nextPC;
    }
    return;
}

void List::renewNTV(RBTree tree){
    PostList* sherlock;
    sherlock=head;
    PostListNode* john;
    while(sherlock!=NULL){
        john=sherlock->first;
        while(john!=NULL){
            Node* src=tree.search(john->key);
            if(strcmp(src->val,john->key)==0)
                if(src->has_voted==1)
                    (sherlock->number_that_voted)++;
            john=john->next;
        }
        sherlock=sherlock->nextPC;
    }
    return;
}

void List::printPercentage(){
    PostList* sherlock;
    sherlock=head;
    float a;
    while(sherlock!=NULL){
        a=100.0*(sherlock->number_that_voted)/(sherlock->number_of_ids);
        printf("# IN %d VOTERS-ARE %f per cent\n",sherlock->postalCode,a);
        sherlock=sherlock->nextPC;
    }
    return;
}

























// PostListNode* PostListNode::addPointNode(Node* vtr){
//     PostListNode *newNode = new PostListNode();
//     newNode->voter=vtr;
//     newNode->next=NULL;
//     return newNode;
// }






// void PostList::addPostListNode(PostList* h, Node* vtr){
//     if(h->first==NULL){
//       h->first= addPointNode(vtr);
//     }else{
//       PostListNode* temp;
//       temp=h->first;
//       while(temp->next!=NULL) temp=temp->next;
//       temp->voter= addPointNode(vtr);
//     }
//     return;
// }

// PostList* newPostList(int k,Node* vtr){
//     PostList *newNode = new PostList();
//     PostListNode temp;
//     temp=newNode(vtr);
//     newNode->first=temp;
//     newNode->nextPC=NULL;
//     newNode->postalCode=k;
//     return newNode;
// }
//
//
// List* List::newList(int k,Node* vtr){
//   Node* newNode=new List();
//   PostList tempNode;
//   tempNode=newPostList(k,vtr);
//   newNode->head=tempNode;
//   return newNode;
// }
//
// void List::addPostal(int k,Node* vtr){
//     PostList* temp=new PostList();
//     temp->postalCode=k;
//     temp.addNode(vtr);
//     if(head==NULL) { // empty list becomes the new node
//       head = temp;
//       return;
//     } else { // find last and link the new node
//           PostList* last = head;
//           while((last->next!=NULL)&&(last->next->postalCode!=k)) last=last->next;
//           if(last->next==NULL)
//             last->next = temp;
//     }
//
//
// }

// void LinkedList::add(episkeptis data){
//   // create node
//     Node* temp = new Node();
//     temp->data = data;
//     temp->next = NULL;
//     if(head==NULL) { // empty list becomes the new node
//         head = temp;
//         this->length++;
//         return;
//     } else { // find last and link the new node
//         Node* last = head;
//         while(last->next) last=last->next;
//         last->next = temp;
//         this->length++;
//     }
// }
