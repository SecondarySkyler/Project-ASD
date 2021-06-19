#ifndef _BST_H
#define _BST_H
#include <map>


class BST {


    public:

        struct node {
            int val;
            node* left;
            node* right;
        };

        BST();
        void insert(int);
        node* find(int);
        void inOrder();
        void polishPrint(std::map<int, std::string>);

        

    private:
        node* root;
        node* insertM(int, node*);
        node* findM(int, node*);
        void inOrderM(node*);
        void polishPrint(std::map<int, std::string>, node*);
};



#endif