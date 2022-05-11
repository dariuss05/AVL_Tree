#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAXNODES 20

/* Data structure for AVL Tree */
typedef struct Node {
    int key, balance;
    struct Node* left, * right;
}Node;

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
            if (*height != 0)
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
            node->right = Insert(node->right, key, height);
            // *height right now is 1, right subtree height is higher
            if (*height != 0) {
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

/* TRAVERSALS
There are 4 Traversals: inOrder, preOrder, postOrder, levelOrder
inOrder takes the route: left->root->right
preOrder takes the route: root->left->right
postOrder takes the route: left->right->root
levelOrder takes the route per level

We're going to use recursion for inOrder, preOrder, postOrder, and for levelOrder we are going to use the height function to get the current level of our tree
*/

void inOrder(struct Node* node) {
    if (node != NULL) {
        inOrder(node->left);
        printf("%d ", node->key);
        inOrder(node->right);
    }
}

void preOrder(struct Node* node) {
    if (node != NULL) {
        printf("%d ", node->key);
        preOrder(node->left);
        preOrder(node->right);
    }
}

void postOrder(struct Node* node) {
    if (node != NULL) {
        postOrder(node->left);
        postOrder(node->right);
        printf("%d ", node->key);
    }
}

/* Function to get the current level of the tree */
void currentLevel(struct Node* node, int level) {
    if (node == NULL)
        return;
    if (level == 1)
        printf("%d ", node->key);
    else if (level > 1) {
        currentLevel(node->left, level - 1);
        currentLevel(node->right, level - 1);
    }
}

void levelOrder(struct Node* node) {
    int height = Height(node);
    for (int i = 1; i <= height; i++)
        currentLevel(node, i);
}


int main(int argc, char** argv) {
    srand(time(NULL));
    struct Node* node = NULL;
    int key = 0, height = 0;

    /* Generating 20 nodes between 0 and 100 */
    printf("initial insertion of keys: ");
    for (int i = 0; i < MAXNODES; i++) {
        key = rand() % 100;
        node = Insert(node, key, &height);
        printf("%d ", key);
    }

    /* Printing traversals */
    
    // inOrder
    printf("\ninOrder traversal: "); inOrder(node);
    printf("\n");

    // postOrder
    printf("postOrder traversal: "); postOrder(node);
    printf("\n");

    // preOrder
    printf("preOrder traversal: "); preOrder(node);
    printf("\n");

    // levelOrder
    printf("levelOrder traversal: "); levelOrder(node);
    printf("\n");
    

    return 0;
}



