#include <iostream>
#include "headers/RBT.hpp"


/**
 * Implementazione funzioni private
 */
RBT::node* RBT::parent(node* tree) {
    return tree->parent;
}

void RBT::balance(node *tree) {

    if (tree->isLeft() && tree->parent->isLeft()) // lo zio se esiste e' right
    {
        if (tree->parent->parent->right == nullptr)
        {
            rightRotate(tree->parent->parent);
            tree->parent->colore = Color::BLACK;
            tree->parent->right->colore = Color::RED;
            return;
        }
        
        // caso 1 sx 
        if (tree->parent->parent->right->colore == Color::BLACK)    
        {
            rightRotate(tree->parent->parent);
            tree->parent->colore = Color::BLACK;
            tree->parent->right->colore = Color::RED;
            return;
        }
        else // zio rosso
        {
            tree->parent->colore = Color::BLACK;
            tree->parent->parent->colore = Color::RED;
            tree->parent->parent->right->colore = Color::BLACK;
            balance(tree->parent->parent);
            return;
        }
        
    } 
    else if ((!tree->isLeft()) && (!tree->parent->isLeft()))
    {
        if (tree->parent->parent->left == nullptr)
        {
            leftRotate(tree->parent->parent);
            tree->parent->colore = Color::BLACK;
            tree->parent->left->colore = Color::RED;
            return;
        }
        // caso 1 dx
        if (tree->parent->parent->left->colore == Color::BLACK)    
        {
            leftRotate(tree->parent->parent);
            tree->parent->colore = Color::BLACK;
            tree->parent->left->colore = Color::RED;
            return;
        }
        else // zio rosso
        {
            tree->parent->colore = Color::BLACK;
            tree->parent->parent->colore = Color::RED;
            tree->parent->parent->left->colore = Color::BLACK;
            balance(tree->parent->parent);
            return;
        }

    }
    else if (tree->isLeft() && !tree->parent->isLeft()) // caso 2 sx
    {
        leftRotate(tree->parent);
        balance(tree->left);
        return;
    }
    else if (!tree->isLeft() && tree->parent->isLeft()) // caso 2 dx
    {
        rightRotate(tree->parent);
        balance(tree->right);
        return;
    }
  
}

RBT::node* RBT::insert(int key, node* tree) {
    if (tree == nullptr)
    {
        tree = new node;
        tree->val = key;
        tree->parent = tree->left = tree->right = nullptr;
        tree->colore = Color::BLACK;
    }
    
    if (key < tree->val)
    {
        if (tree->left == nullptr)
        {
            tree->left = new node;
            tree->left->val = key;
            tree->left->parent = tree;
            tree->left->left = tree->left->right = nullptr;
            tree->left->colore = Color::RED;
            if (tree->colore == Color::RED)
            {
                balance(tree->left);
            }
        }
        else
        {
            tree->left = insert(key, tree->left);
        }    


    }
    else if (key > tree->val)
    {
        if (tree->right == nullptr)
        {
            tree->right = new node;
            tree->right->val = key;
            tree->right->parent = tree;
            tree->right->left = tree->right->right = nullptr;
            tree->right->colore = Color::RED;
            if (tree->colore == Color::RED)
            {
                balance(tree->right);
            }
        }
        else
        {
            tree->right = insert(key, tree->right);
        }
    }

    // check the need to restablish the invariant
    // if (tree->parent != NULL && tree->colore == Color::RED && tree->parent->colore == Color::RED)
    // {
    //     balance(tree);
    // }
    
    
    return tree;
}

RBT::node* RBT::find(int keyToFind, node* tree) {
    if (tree == nullptr)
        return nullptr;
    else if (keyToFind = tree->val) 
        return tree;
    else if (keyToFind < tree->val) 
        return find(keyToFind, tree->left);
    else if (keyToFind > tree->val)
        return find(keyToFind, tree->right);
    else
        return nullptr;
}

void RBT::leftRotate(node* tree) {
    node *right_child = tree->right;
    tree->right = right_child->left;

    if (tree->right != nullptr)
    {
        tree->right->parent = tree;
    }
    right_child->parent = tree->parent;

    if (tree->parent == nullptr)
        tree = right_child;
    else if (tree == tree->parent->left)
        tree->parent->left = right_child;
    else
        tree->parent->right = right_child;

    right_child->left = tree;
    tree->parent = right_child;
}


void RBT::rightRotate(node* tree) {
    node *left_child = tree->left;
    tree->left = left_child->right;

    if (tree->left != nullptr)
        tree->left->parent = tree;

    left_child->parent = tree->parent;

    if (tree->parent == nullptr)
        root = left_child;
    else if (tree == tree->parent->left)
        tree->parent->left = left_child;
    else
        tree->parent->right = left_child;

    left_child->right = tree;
    tree->parent = left_child;

}

void RBT::inOrder(node *tree) {
    if (tree != nullptr)
    {
        inOrder(tree->left);
        std::cout << tree->val << std::endl;
        inOrder(tree->right);
    }
}

int RBT::heightChecker(node* n) {
    int count = 1;
    while (n->right != nullptr)
    {
        n = n->right;
        count++;
    }
    return count;
}

/**
 * Implementazione funzioni pubbliche
 */

RBT::RBT() {
    root = nullptr;
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

int RBT::heightChecker() {
    return heightChecker(root);
}

int main(int argc, char const *argv[])
{
    RBT tree;
    tree.insert(5);
    tree.insert(24);
    tree.insert(34);
    // tree.inOrder();
   
   
   
   
    // for (int i = 0; i < 100; i++)
    // {
    //     tree.insert(i);
    // }
    int h = tree.heightChecker();
    std::cout << h << std::endl;
    

    return 0;
}
