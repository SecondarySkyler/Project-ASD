#ifndef _RBT_H
#define _RBT_H

class RBT {
        
    public:
        struct node {
            int val;
            node* left;
            node* right;
        };

        RBT();
        void insert(int);
        node* find(int);
        void inOrder();
        
    private:
        node* root;
        node* insert(int, node*);
        node* find(int, node*);
        node* leftRotate(node*&);
        node* rightRotate(node*&);
        void inOrder(node*);
};



#endif