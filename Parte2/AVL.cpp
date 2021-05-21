#include <iostream>
#include <algorithm>

class AVL {
    struct node {
        int val;
        node* left;
        node* right;
        int height;
    };

    node* root;

    // funzioni ausiliarie, utili quando nodo* punta a null
    int height(node* n) {
        return (n == NULL)? 0 : n->height;
    }

    int balance(node* n) {
        return (n == NULL)? 0 : height(n->left) - height(n->right);
    }

    node* createNode(int k) {
        node* x;
        x->height = 1; // foglia
        x->val = k;
        x->left = NULL;
        x->right = NULL;
        return(x);
    }

    node* leftRotate(node *x) {
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

    node* rightRotate(node* y) {
        node *x = y->left;
        node *T2 = x->right;
    
        // rotazione
        x->right = y;
        y->left = T2;
    
        // aggiorno altezze
        y->height = std::max(height(y->left), height(y->right)) + 1;
        x->height = std::max(height(x->left), height(x->right)) + 1;
    
        // return nuova radice
        return x;
    }

    node* insert_rec(node* x, int key) {
        // normale inserimento BST
        if(x == NULL) {
            return(newNode(key));
        }
    
        if(key < x->key) {
            x->left = insert(x->left, key);
        } else if(key > x->key) {
            x->right = insert(x->right, key);
        }else return x;
            
        // aggiornamento altezza x
        x->height = 1 + max(height(x->left), height(x->right));
    
        int bal = balance(x);
    
        // 4 casi se il sottoalbero in x è sbilanciato
        if (bal > 1 && key < x->left->key) {
            return rightRotate(x);
        }
        
        if (bal < -1 && key > x->right->key) {
            return leftRotate(x);
        }

        if (bal > 1 && key > x->left->key) {
            x->left = leftRotate(x->left);
            return rightRotate(x);
        }

        if (bal < -1 && key < x->right->key) {
            x->right = rightRotate(x->right);
            return leftRotate(node);
        }
        
        return x;
    }

    public:
        void insert(int);
        node* search(int);
        void preOrder(void);
        void inOrder(void);
        void postOrder(void);
};

void AVL::insert(int key) {
    root = insert_rec(root, key);
}

void AVL::preOrder(void) {
    if(root != NULL) {
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

void AVL::inOrder(void) {
    if(root != NULL) {
        inOrder(root->left);
        cout << root->key << " ";
        inOrder(root->right);
    }
}

void AVL::postOrder(void) {
    if(root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        cout << root->key << " ";
    }
}

