#include <iostream>
#include "headers/RBT.hpp"


/**
 * Implementazione funzioni private
 */
RBT::node* RBT::parent(node* tree) {
    return tree->parent;
}

RBT::node* RBT::insert(int key, node* tree) {
    if (tree == NULL)
    {
        tree = new node;
        tree->val = key;
        tree->left = tree->right = NULL;
        tree->colore = Color::RED;
    }
    // more to add
    if (parent(tree) == NULL)
    {
        tree->colore = Color::BLACK;
    }

    if (key < tree->val)
        tree->left = insert(key, tree->left);
    else if (key > tree->val)
        tree->right = insert(key, tree->right);
    
    return tree;
}

RBT::node* RBT::find(int keyToFind, node* tree) {
    if (tree == NULL)
        return NULL;
    else if (keyToFind = tree->val) 
        return tree;
    else if (keyToFind < tree->val) 
        return find(keyToFind, tree->left);
    else if (keyToFind > tree->val)
        return find(keyToFind, tree->right);
    else
        return NULL;
}

/**
 * Implementazione funzioni pubbliche
 */

RBT::RBT() {
    root = NULL;
}

void RBT::insert(int key) {
    root = insert(key, root);
}

RBT::node* RBT::find(int keyToFind) {
    return find(keyToFind, root);
}

void RBT::inOrder() {
    inOrder(root);
}