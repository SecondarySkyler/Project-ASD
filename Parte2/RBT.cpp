#include <iostream>
#include "headers/RBT.hpp"


/**
 * Implementazione funzioni private
 */
RBT::node* RBT::insert(int key, node* tree) {
    if (tree == NULL)
    {
        tree = new node;
        tree->val = key;
        tree->left = tree->right = NULL;
        tree->colore = Color::BLACK;
    }
    // more to add
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