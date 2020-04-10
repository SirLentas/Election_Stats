#include"redblack.h"


class PostListNode{
    public:
    char* key;
    PostListNode* next;

};

class PostList{
    public:
    int postalCode;
    PostList* nextPC;
    PostListNode* first;
    int number_that_voted;
    int number_of_ids;

    void addPostListNode(char*);
    PostList(){
        number_of_ids=0;
        number_that_voted=0;
    }
};


class List{
    public:
    PostList* head;

    List();
    ~List();
    bool searchPostalCode(int);
    PostList* returnPostList(int);
    void addInPostal(PostList*,char*);
    void addNewPostal(int,char*);
    void print();//for testing in terminal
    void deletefromList(char*);
    void renewNTV(RBTree tree);
    void printPercentage();
};
