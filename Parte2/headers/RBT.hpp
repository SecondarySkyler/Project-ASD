#ifndef _RBT_H
#define _RBT_H

class RBT {
        
    public:
        enum class Color {BLACK, RED};

        struct node {
            int val;
            node* parent;
            node* left;
            node* right;
            Color colore;
        };

        RBT();
        void insert(int);
        node* find(int);
        void inOrder();
        
    private:
        node* root;
        node* parent(node*);
        node* insert(int, node*);
        node* find(int, node*);
        node* leftRotate(node*&);
        node* rightRotate(node*&);
        void inOrder(node*);
};



#endif