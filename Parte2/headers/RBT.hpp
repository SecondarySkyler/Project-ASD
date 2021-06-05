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
            bool isLeft() {
                return this != nullptr && parent!= nullptr && val < parent->val; 
            }
        };

        RBT();
        void insert(int);
        node* find(int);
        void inOrder();
        int heightChecker();
        
    private:
        node* root;
        node* parent(node*);
        node* balance(node*);
        node* insert(int, node*);
        node* find(int, node*);
        node* leftRotate(node*);
        node* rightRotate(node*);
        void inOrder(node*);
        int heightChecker(node*);
};



#endif