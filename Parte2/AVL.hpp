#ifndef _AVL_H
#define _AVL_H



class AVL {
    public:
        struct node {
            int val;
            node* left;
            node* right;
            int height;
        };
        AVL();
        void insert(int);
        node* search(int);
        void preOrder(void);
        void inOrder(void);
        void postOrder(void);
    private:
        node* root;

        int height(node*);
        int balance(node*);
        node* createNode(int);
        node* leftRotate(node*);
        node* rightRotate(node*);
        node* insert_rec(node*, int);
        node* search_rec(int, node*);
        void preOrder(node*);
        void inOrder(node*);
        void postOrder(node*);
};

#endif