#include <iostream>
using namespace std;


class BST
{

    struct node {
        int val;
        node* left;
        node* right;
        node* parent;
    };

    node* root;

    node* insert(int key, node* tree) {
        if (tree == NULL)
        {
            tree = new node;
            tree->val = key;
            tree-> left = tree->right = NULL;
        } 
        else if(key < tree->val)
            tree->left = insert(key, tree->left);
        else if(key > tree->val)
            tree->right = insert(key, tree->right);
        
        return tree;
    }

    node* find(int keyToFind, node* tree) {
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



public:
    BST() {
        root = NULL;
    }
    

    void insert(int key) {
        root = insert(key, root);
    }

    node* find(int key) {
        return find(key, root);
    }
};

int main(int argc, char const *argv[])
{
    BST tree;
    tree.insert(20);
    tree.insert(23);
    tree.insert(18);
    tree.insert(26);
    tree.insert(15);
    tree.insert(17);
    tree.insert(9);
    if (tree.find(17) != NULL)
    {
        cout << "dio" << endl;
    }
    

    return 0;
}




