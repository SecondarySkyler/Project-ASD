#ifndef _BST_H
#define _BST_H



class BST {
    private:
        struct node;
        
        node* root;

        node* insert(int, node*);
        node* find(int, node*);

    public:
        BST();
        void insert(int key);
        node* find(int);
        void inOrder(node*);
};

#endif