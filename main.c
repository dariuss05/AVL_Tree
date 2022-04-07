#include <stdio.h>
#include <stdlib.h>
#define MAXNODES 100

/* Data structure for AVL Tree
I'm using balance instead of height to complicate things */
typedef struct Node {
    int key, balance;
    struct Node* left, * right;
};

int noBalanceCount = 0; // Counter variable for all the balances made;

/* Function to determine the height of the AVL Tree */
int Height(struct Node* node) {
    int heightLeft, heightRight;

    // Check if node is NULL
    if (node == NULL)
        return 0;

    // Getting height by using recursion
    if (node != NULL) {
        heightLeft = Height(node->left);
        heightRight = Height(node->right);

        // Getting the maximum value between these two
        int maximumValue = 0;
        if (heightLeft > heightRight)
            maximumValue = heightLeft;
        else
            maximumValue = heightRight;
        maximumValue++;
        return maximumValue;
    }
}

/* Insertion Function by going through all cases based of the balance factor */
struct Node* Insert(struct Node* node, const int key, int* height) {
    struct Node* p1, * p2;

    // If node is NULL, we initalize
    if (node == NULL) {
        node = (struct Node*)malloc(sizeof(struct Node));
        node->left = NULL;
        node->right = NULL;
        node->key = key;
        node->balance = 0;
        *height = 1;
    }

    // Checking if key to-be inserted is less than the node, then we insert in the left sub tree

    else {
        if (key < node->key) {
            node->left = Insert(node->left, key, height);
            // Factor of balance cases:
            if (*height != NULL)
                switch (node->balance) {
                case 1:
                    node->balance = 0;
                    *height = 0;
                    break;
                case 2:
                    node->balance = -1;
                    *height = 0;
                    break;
                case -1: // Re-balance of tree
                    noBalanceCount++;
                    p1 = node->left;
                    // Left Case:
                    if (p1->balance == -1) {
                        node->left = p1->right;
                        p1->right = node;
                        node->balance = 0;
                        node = p1;
                    }
                    // Left Right Case:
                    else {
                        p2 = p1->right;
                        p1->right = p2->left;
                        p2->left = p1;
                        node->left = p2->right;
                        p2->right = node;
                        if (node->balance == -1)
                            node->balance = 1;
                        else
                            node->balance = 0;
                        if (p2->balance == 1)
                            p1->balance = -1;
                        else
                            p1->balance = 0;
                        node = p2;
                    }
                    node->balance = 0;
                    *height = 0;
                    break;
                } // final switch;
        }
        // If the key to-be inserted is higher than the node, then we insert in the right subtree
        else if (key > node->key) {
            node->right = insert(node->right, key, *height);
            // *height right now is 1, right subtree height is higher
            if (*height != NULL) {
                // Factor of balance cases:
                switch (node->balance) {
                case -1:
                    node->balance = 0;
                    *height = 0;
                    break;
                case 0:
                    node->balance = 1;
                    break;
                case 1:
                    // Re-balance tree:
                    noBalanceCount++;
                    p1 = node->right;
                    // Right case:
                    if (p1->balance == 1) {
                        node->right = p1->left;
                        p1->left = node;
                        node->balance = 0;
                        node = p1;
                    }
                    // Right left case:
                    else {
                        p2 = p1->left;
                        p1->left = p2->right;
                        p2->right = p1;
                        node->right = p2->left;
                        p2->left = node;
                        if (p2->balance == 1)
                            node->balance = -1;
                        else
                            node->balance = 0;
                        if (p2->balance == -1)
                            p1->balance = 1;
                        else
                            p1->balance = 0;
                        node = p2;
                    }
                    node->balance = 0;
                    *height = 0;
                    break;
                } // final switch;
            }
        }
    }
    return node;
}