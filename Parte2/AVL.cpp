#include <iostream>
#include "AVL.hpp"

/*
*
*       private:
*
*/

// funzioni ausiliarie, utili quando nodo* punta a null
int AVL::height(node* n) {
    return (n == NULL)? 0 : n->height;
}

int AVL::balance(node* n) {
    return (n == NULL)? 0 : height(n->left) - height(n->right);
}

AVL::node* AVL::leftRotate(node* &x) {
    node* y = x->right;

    // rotazione
    x->right = y->left;
    y->left = x;
    
    // aggiorno altezze
    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(x->right), height(x)) + 1;

    // return nuova radice
    return y;
}

AVL::node* AVL::rightRotate(node* &x) {
    node* y = x->left;

    // rotazione
    x->left = y->right;
    y->right = x;

    // aggiorno altezze
    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(x)) + 1;

    // return nuova radice
    return x;
}

AVL::node* AVL::insert(node* x, int key) {
    // normale inserimento BST
    if(x == NULL) {
        x = new node;
        x->val = key;
        x->height = 0;
        x->left = x->right = NULL;
    }

    else if (key < x->val) {
        x->left = insert(x->left, key);
        if(height(x->left) - height(x->right) == 2)
            {
                if(key < x->left->val)
                    x = rightRotate(x);
                else {
                    x->left = leftRotate(x->left);
                    x = rightRotate(x);
                }
            }
    }
    else if (key > x->val) {
        x->right = insert(x->right, key);
        if(height(x->right) - height(x->left) == 2)
        {
            if(key > x->right->val)
                x = leftRotate(x);
            else {
                x->right = rightRotate(x->right);
                x = leftRotate(x);
            }
        }
    }
        
    // aggiornamento altezza x
    x->height = 1 + std::max(height(x->left), height(x->right));

    return x;
}

AVL::node* AVL::find(int key, node* x) {
    if (x == NULL)
        return NULL;
    else if (key = x->val) 
        return x;
    else if (key < x->val) 
        return find(key, x->left);
    else if (key > x->val)
        return find(key, x->right);
    else
        return NULL;  
}

void AVL::preOrder(node* x) {
    if(x != NULL) {
        std::cout << x->val << " ";
        preOrder(x->left);
        preOrder(x->right);
    }
}

void AVL::inOrder(node* x) {
    if(x != NULL) {
        inOrder(x->left);
        std::cout << x->val << " ";
        inOrder(x->right);
    }
}

void AVL::postOrder(node* x) {
    if(x != NULL) {
        postOrder(x->left);
        postOrder(x->right);
        std::cout << x->val << std::endl;
    }
}

/*
*
*       public:
*
*/

AVL::AVL() {
    root = NULL;
}

void AVL::insert(int key) {
    root = insert(root, key);
}

AVL::node* AVL::find(int key) {
    return find(key, root);
}

void AVL::preOrder(void) {
    preOrder(root);
}

void AVL::inOrder(void) {
    inOrder(root);
}

void AVL::postOrder(void) {
    postOrder(root);
}

