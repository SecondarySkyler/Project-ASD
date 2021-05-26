#include <iostream>
#include "headers/RBT.hpp"


/**
 * Implementazione funzioni private
 */


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