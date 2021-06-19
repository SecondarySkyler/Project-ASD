#include <iostream>
#include "headers/BST.hpp"


BST::BST() {
    root = NULL;
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

void BST::polishPrint(std::map<int, std::string> mappa, node* root) {
    if (root != nullptr)
    {
        std::cout << root->val << ":" << mappa[root->val] << " ";
        polishPrint(mappa, root->left);
        polishPrint(mappa, root->right);
    }
    else
    {
        std::cout << "NULL" << " ";
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

void BST::polishPrint(std::map<int, std::string> mappa) {
    return polishPrint(mappa, root);
}

int main() {
    BST tree;
    std::string operazione;
    int numberToInsert;
    std::string numberLiteral;
    std::map<int, std::string> number_literal;
    while (operazione != "exit")
    {
        std::cin >> operazione;
        if (operazione == "insert")
        {
            std::cin >> numberToInsert;
            std::cin >> numberLiteral;
            number_literal[numberToInsert] = numberLiteral;
            tree.insert(numberToInsert);
        }
        else if (operazione == "show")
        {
            tree.polishPrint(number_literal);
            std::cout << std::endl;
        }
        else if (operazione == "find")
        {
            int numberToFind;
            std::cin >> numberToFind;
            BST::node* searchedNode = tree.find(numberToFind);
            if (searchedNode != nullptr) 
            {
                std::cout << number_literal[searchedNode->val] << std::endl;
            }
            else 
            {
                std::cout << "Not Found";
            }
        }
        else 
        {
            return 0;
        }
        
    }   
}







