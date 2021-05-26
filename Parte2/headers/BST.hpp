#ifndef _BST_H
#define _BST_H



class BST {


    public:

        struct node {
            int val;
            node* left;
            node* right;
        };

        BST();
        void insert(int);
        node* find(int);
        void inOrder();
        

    private:
        node* root;
        node* insertM(int, node*);
        node* findM(int, node*);
        void inOrderM(node*);
};



#endif