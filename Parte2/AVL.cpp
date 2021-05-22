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

AVL::node* AVL::createNode(int k) {
    node* x;
    x->height = 1; // foglia
    x->val = k;
    x->left = NULL;
    x->right = NULL;
    return(x);
}

AVL::node* AVL::leftRotate(node* x) {
    node *y = x->right;
    node *T2 = y->left;

    // rotazione
    y->left = x;
    x->right = T2;

    // aggiorno altezze
    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;

    // return nuova radice
    return y;
}

AVL::node* AVL::rightRotate(node* y) {
    node* x = y->left;
    node* T2 = x->right;

    // rotazione
    x->right = y;
    y->left = T2;

    // aggiorno altezze
    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;

    // return nuova radice
    return x;
}

AVL::node* AVL::insert_rec(node* x, int key) {
    // normale inserimento BST
    if(x == NULL) {
        return(createNode(key));
    }

    if (key < x->val) 
        x->left = insert_rec(x->left, key);
    else if (key > x->val) 
        x->right = insert_rec(x->right, key);
    else return x;
        
    // aggiornamento altezza x
    x->height = 1 + std::max(height(x->left), height(x->right));

    int bal = balance(x);

    // 4 casi se il sottoalbero in x è sbilanciato
    if (bal > 1 && key < x->left->val) return rightRotate(x);
    
    if (bal < -1 && key > x->right->val) return leftRotate(x);

    if (bal > 1 && key > x->left->val) {
        x->left = leftRotate(x->left);
        return rightRotate(x);
    }

    if (bal < -1 && key < x->right->val) {
        x->right = rightRotate(x->right);
        return leftRotate(x);
    }
    
    return x;
}

AVL::node* AVL::search_rec(int key, node* x) {
    if (x == NULL)
        return NULL;
    else if (key = x->val) 
        return x;
    else if (key < x->val) 
        return search_rec(key, x->left);
    else if (key > x->val)
        return search_rec(key, x->right);
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
        std::cout << x->val << " ";
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
    root = insert_rec(root, key);
}

AVL::node* AVL::search(int key) {
    return search_rec(key, root);
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

