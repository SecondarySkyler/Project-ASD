#ifndef _BST_H
#define _BST_H



class BST {
    private:
        struct node {
            int val;
            node* left;
            node* right;
        };
        
        node* root;

        node* insert(int, node*);
        node* find(int, node*);

    public:
        BST();
        void insert(int key);
        node* find(int);
};

#endif