#include <iostream>
#include "../headers/BST.hpp"


BST::BST() {
    root = NULL;
}

BST::~BST() { 
    delete root;
}

BST::node::~node() {
    if (left != nullptr)
    {
        delete left;
    }
    
    if (right != nullptr)
    {
        delete right;
    }

}

BST::node* BST::insertM(int key, node* tree) {
    if (tree == NULL)
        {
            tree = new node;
            tree->val = key;
            tree-> left = tree->right = NULL;
        } 
        else if(key < tree->val)
            tree->left = insertM(key, tree->left);
        else if(key > tree->val)
            tree->right = insertM(key, tree->right);
        
        return tree;
}

BST::node* BST::findM(int keyToFind, node* tree) {
    if (tree == NULL)
        return NULL;
    else if (keyToFind == tree->val) 
        return tree;
    else if (keyToFind < tree->val) 
        return findM(keyToFind, tree->left);
    else if (keyToFind > tree->val)
        return findM(keyToFind, tree->right);
    else
        return NULL;
}

void BST::inOrderM(node *tree) {
    if (tree != NULL)
    {
        inOrderM(tree->left);
        std::cout << tree->val << std::endl;
        inOrderM(tree->right);
    }
}

/**
 * 
 * IMPLEMENTAZIONE FUNZIONI PUBBLICHE
 * 
 */

void BST::insert(int key) {
    root = insertM(key, root);
}

BST::node* BST::find(int keyToFind) {
    return findM(keyToFind, root);
}

void BST::inOrder() {
    inOrderM(root);
}