#include <iostream>
#include "headers/RBT.hpp"


/**
 * Implementazione funzioni private
 */
RBT::node* RBT::retrieveUncle(node* nephew, bool *zioPosition) {
    if (nephew != nullptr && nephew->parent != nullptr && nephew->parent->parent != nullptr)
    {
        if (isLeft(nephew->parent)) // se true => padre e' sinistro => zio e' destro
        {
            *zioPosition = isLeft(nephew);
            return nephew->parent->parent->right;
        }
        else
        {
            *zioPosition = !isLeft(nephew);
            return nephew->parent->parent->left;
        }   
    }
    return nullptr;
}

RBT::node* RBT::fixTree(node *tree) {
    if (tree != nullptr && tree->parent != nullptr && tree->parent->colore == Color::RED)
    {
        bool isLeftSon = isLeft(tree);
        bool isLeftZio = true;
        node *zio = retrieveUncle(tree, &isLeftZio);
        if ( (zio == nullptr || zio->colore == Color::BLACK) && isLeftZio ) // se zio anche opposto => caso 1
        {
            tree->parent->parent->colore = Color::RED;
            tree->parent->colore = Color::BLACK;
            tree = isLeftSon ? rightRotate(tree->parent) : leftRotate(tree->parent);
        } 
        else if (zio == nullptr || zio->colore == Color::BLACK) // se zio NON opposto => caso 2
        {
            tree = isLeftSon ? rightRotate(tree->parent) : leftRotate(tree->parent);
            tree = fixTree(tree->parent);
        }
        else { // zio opposto e rosso => caso 3
            tree->parent->colore = zio->colore = Color::BLACK;
            tree->parent->parent->colore = Color::RED;
            tree = fixTree(tree->parent->parent);
        }
    }
    else if (tree != nullptr && tree->parent == nullptr)
    {
        tree->colore = Color::BLACK;
        root = tree;
    }
    return tree;
}
/**
 * @tree è il figlio appena inserito
 */
// RBT::node* RBT::balance(node *tree) {

//     if (tree->isLeft() && tree->parent->isLeft()) // lo zio se esiste e' right
//     {
//         if (tree->parent->parent->right == nullptr)
//         {
//             tree = rightRotate(tree->parent->parent);
//             tree->parent->colore = Color::BLACK;
//             tree->parent->right->colore = Color::RED;
//             return tree;
//         }
        
//         // caso 1 sx 
//         if (tree->parent->parent->right->colore == Color::BLACK)    
//         {
//             tree = rightRotate(tree->parent->parent);
//             tree->parent->colore = Color::BLACK;
//             tree->parent->right->colore = Color::RED;
//             return tree;
//         }
//         else // zio rosso
//         {
//             tree->parent->colore = Color::BLACK;
//             tree->parent->parent->colore = Color::RED;
//             tree->parent->parent->right->colore = Color::BLACK;
//             tree = balance(tree->parent->parent);
//             return tree;
//         }
        
//     } 
//     else if ((!tree->isLeft()) && (!tree->parent->isLeft()))
//     {
//         if (tree->parent->parent->left == nullptr)
//         {
//             tree = leftRotate(tree->parent->parent);
//             tree->colore = Color::BLACK;
//             tree->left->colore = Color::RED;
//             return tree;
//         }
//         // caso 1 dx
//         if (tree->parent->parent->left->colore == Color::BLACK)    
//         {
//             tree = leftRotate(tree->parent->parent);
//             tree->colore = Color::BLACK;
//             tree->left->colore = Color::RED;
//             return tree;
//         }
//         else // zio rosso
//         {
//             tree->parent->parent->colore = Color::RED;
//             tree->parent->colore = Color::BLACK;
//             tree->parent->parent->left->colore = Color::BLACK;
//             tree = balance(tree->parent->parent);
//             return tree;
//         }

//     }
//     else if (tree->isLeft() && !tree->parent->isLeft()) // caso 2 sx
//     {
//         tree = leftRotate(tree->parent);
//         tree = balance(tree->left);
//         return tree;
//     }
//     else if (!tree->isLeft() && tree->parent->isLeft()) // caso 2 dx
//     {
//         tree = rightRotate(tree->parent);
//         tree = balance(tree->right);
//         return tree;
//     }
//   return tree;
// }

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
            // tree = tree->left;
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
            // tree = tree->right;
        }
        else
        {
            tree->right = insert(key, tree->right);
        }
    }
    
    if (tree->parent != nullptr && tree->parent->parent != nullptr && tree->parent->colore == Color::RED)
    {
        tree = fixTree(tree);
    }

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

RBT::node* RBT::leftRotate(node *tree) {
    node *grandFather = tree;
    node *right_child = tree->right;
    tree->right = right_child->left;

    if (tree->right != nullptr)
        tree->right->parent = tree;
    
    right_child->parent = tree->parent;

    if (tree->parent == nullptr)
        root = right_child;
    else if (tree == tree->parent->left)
        tree->parent->left = right_child;
    else
        tree->parent->right = right_child;

    right_child->left = grandFather;
    grandFather->parent = right_child;

    return right_child;
}

// tree viene passato come genitore del nodo appena inserito
RBT::node* RBT::rightRotate(node *tree) {
    node *dad = tree->parent;
    node *rightSon = tree->right;

    if (dad != root)
    {
        if (dad == dad->parent->left)
        {
            tree->parent->parent->left = tree;
        }
        else
        {
            tree->parent->parent->right = tree;
        }
        tree->parent = dad->parent;
    }
    else
    {
        root = tree;
        tree->parent = nullptr;
    }
    tree->right = dad;
    dad->left = rightSon;
    dad->parent = tree;
    if (rightSon != nullptr)
    {
        rightSon->parent = dad;
    }
    
    return tree;
    
    
    // if (tree->left != nullptr)
    //     tree->left->parent = tree;

    // left_child->parent = tree->parent;

    // if (tree->parent == nullptr)
    //     root = left_child;
    // else if (tree == tree->parent->left)
    //     tree->parent->left = left_child;
    // else
    //     tree->parent->right = left_child;

    // left_child->right = tree;
    // tree->parent = left_child;
    // grandFather->parent = left_child;

    // return tree;
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
    int count = 0;
    while (n->right != nullptr)
    {
        n = n->right;
        count++;
    }
    return count;
}

int RBT::leftHeightChecker(node* root) {
    int count = 0;
    while (root->left != nullptr)
    {
        root = root->left;
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

int RBT::leftHeightChecker() {
    return  leftHeightChecker(root);
}

int main(int argc, char const *argv[])
{
    RBT tree;
    // tree.insert(34);
    // tree.insert(24);
    // tree.insert(5);
   
   
   
   
    for (int i = 10; i > 1; i--)
    {
        tree.insert(i);
    }
    tree.inOrder();
    int h = tree.leftHeightChecker();
    std::cout << h << std::endl;
    

    return 0;
}
