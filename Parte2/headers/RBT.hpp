#ifndef _RBT_H
#define _RBT_H
#include <map>

class RBT {
        
    public:
        enum class Color {BLACK, RED};

        struct node {
            int val;
            node* parent;
            node* left;
            node* right;
            Color colore;
            bool isLeft() {
                return this != nullptr && parent!= nullptr && val < parent->val; 
            }
        };

        RBT();
        void insert(int);
        node* find(int);
        void inOrder();
        int heightChecker();
        int leftHeightChecker();
        int blackHeight();
        #define isLeft(x) (x->parent->left == x ? true : false)
        void polishPrint(std::map<int, std::string>);

        
    private:
        node* root;
        node* parent(node*);
        node* balance(node*);
        node* insert(int, node*&);
        node* bstInsert(node*, node*&);
        node* find(int, node*);
        node* leftRotate(node*);
        node* rightRotate(node*);
        void inOrder(node*);
        int heightChecker(node*);
        int leftHeightChecker(node*);
        int blackHeight(node*);
        node* fixTree(node*);
        node* retrieveUncle(node*, bool*);
        node* createNode(int);
        void polishPrintPrivate(std::map<int, std::string>, node*);
};



#endif