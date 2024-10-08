#ifndef _AVL_H
#define _AVL_H



class AVL {
    public:
        struct node {
            int val;
            node* left;
            node* right;
            int height;
            ~node();
        };
        AVL();
        ~AVL();
        void insert(int);
        node* find(int);
        void preOrder(void);
        void inOrder(void);
        void postOrder(void);
        int heightChecker();
    private:
        node* root;

        int height(node*);
        int balance(node*);
        node* leftRotate(node*&);
        node* rightRotate(node*&);
        node* insert(node*, int);
        node* find(int, node*);
        void preOrder(node*);
        void inOrder(node*);
        void postOrder(node*);
        int heightChecker(node*,int);
};

#endif