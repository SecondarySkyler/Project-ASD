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

// qui viene passato il nodo appena inserito
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
            tree = isLeftSon ? rightRotate(tree) : leftRotate(tree);
            tree = isLeftSon ? fixTree(tree->right) : fixTree(tree->left);
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

RBT::node* RBT::bstInsert(node *nodo, node *&root) {
    node *n = root;
    node *aux = nullptr;

    while (n != nullptr)
    {
        aux = n;
        if (nodo->val < n->val)
        {
            n = n->left;
        } else {
            n = n->right;
        }
    }
    

    if (aux == nullptr)
    {
        root = nodo;
    } else {
        nodo->parent = aux;
        if (nodo->val < aux->val)
        {
            aux->left = nodo;
        } else {
            aux->right = nodo;
        }
    }

    return root;
}

RBT::node* RBT::createNode(int key) {
    node* newNode = new node;
    newNode->val = key;
    newNode->left = newNode->right = newNode->parent = nullptr;
    return newNode;
}

RBT::node* RBT::insert(int key, node *&root) {
    node* nodo = createNode(key);
    root = bstInsert(nodo, root);

    nodo->colore = nodo == root ? Color::BLACK : Color::RED;

    if (nodo->parent != nullptr && nodo->parent->parent != nullptr && nodo->parent->colore == Color::RED)
    {
        nodo = fixTree(nodo);
    }

    return root;
}

RBT::node* RBT::find(int keyToFind, node* tree) {
    if (tree == nullptr || tree->val == keyToFind) {
        return tree;
    } else if (keyToFind > tree->val) {
        return find(keyToFind, tree->right);
    } else {
        return find(keyToFind, tree->left);
    }
}

// assumo che tree sia il genitore del nodo appena inserito
RBT::node* RBT::leftRotate(node *tree) {
    node *dad = tree->parent; // sarebbe il nonno del nodo appena inserito
    node *leftSon = tree->left;

    if (dad->parent != nullptr)
    {
        if (dad == dad->parent->left) // si controlla se il nonno è un figlio sinistro
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
    dad->right = leftSon;
    dad->parent = tree;
    tree->left = dad;
    if (leftSon != nullptr)
    {
        leftSon->parent = dad;
    }
    
    return tree;
}

// tree viene passato come genitore del nodo appena inserito
RBT::node* RBT::rightRotate(node *tree) {
    node *dad = tree->parent;
    node *rightSon = tree->right;

    if (dad->parent != nullptr)
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

int RBT::leftHeightChecker(node* root) {
    int count = 0;
    while (root->left != nullptr)
    {
        root = root->left;
        count++;
    }
    return count;
}

int RBT::blackHeight(node* root) {
    if (root == nullptr) return 0;
    else
    {
        int bh = root->colore == Color::BLACK ? 1 : 0;
        return bh + blackHeight(root->right);
    }
}

void RBT::polishPrintPrivate(std::map<int, std::string> mappa, node* root) {
    if (root != nullptr)
    {
        
        std::cout << root->val << ":" << mappa[root->val] << ":";
        Color rootColor = root->colore;
        switch (rootColor)
        {
            case Color::BLACK : std::cout << "Black" << " "; break;
            case Color::RED : std::cout << "Red" << " "; break;
        }

        polishPrintPrivate(mappa, root->left);
        polishPrintPrivate(mappa, root->right);
    }
    else 
    {
        std::cout << "NULL" << " ";
    }  
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

int RBT::blackHeight() {
    return blackHeight(root);
}

void RBT::polishPrint(std::map<int, std::string> mappa) {
    return polishPrintPrivate(mappa, root);
}

int main() {
    RBT tree;
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
            RBT::node* searchedNode = tree.find(numberToFind);
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
